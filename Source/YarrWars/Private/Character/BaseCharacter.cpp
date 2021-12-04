// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"

#include "Character/CharacterAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"
#include "Character/AICharacter.h"
#include "Controllers/WaveController.h"
#include "Character/PlayerCharacter.h"
#include "Character/CharacterAccessory.h"
// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set the location of the mesh to the bottom so the feet touch the ground
	// Also set the rotation so the character is facing the forward direction
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));

	// Set load on play to false as default
	loadOnPlay = false;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	// Create the weapon mesh & attach it to the weapon socket on the mesh
	weaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WEAPON"));
	weaponMesh->SetupAttachment(GetMesh(), FName(TEXT("WeaponSocket")));

	// Create the weapon collider and attach it to the weapon mesh
	weaponCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	weaponCollider->SetupAttachment(weaponMesh);

	// Disable collision to prevent triggering it when we aren't attacking
	weaponCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// Allows overlap events for the weapon
	//GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	//GetCapsuleComponent()->SetCollisionProfileName("OverlapAll");
	weaponCollider->SetGenerateOverlapEvents(true);				
	weaponCollider->SetCollisionProfileName("OverlapAll");

	// Create the audio component & attach it to the root component
	audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	audioComponent->SetupAttachment(RootComponent);

	




	
}

/// <summary>
///	Sets the new state on this class as well as the anim instance
/// </summary>
/// <param name="state">New state we want to set </param>
void ABaseCharacter::SetCharacterState(ECharacterState state)
{
	characterState = state;			// Set the new character state
	// Cast to the anim instance & set the state
	if(auto anim = Cast<UCharacterAnimInstance>(characterAnim))
	{
		anim->SetCharacterState(state);
	}
}


// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	// If we are loading the character when we run than game, than call the setup
	if(loadOnPlay)
	{
		SetupCharacter(characterType);
	}


	// GET THE WAVE CONTROLLER
	{
		TArray<AActor*> outActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWaveController::StaticClass(), outActors);
		if(outActors.Num() > 0)
			waveController = Cast<AWaveController>(outActors[0]);
	}
	

	
	characterState = ECharacterState::IDLE;			// Set the state to idle

	// Set the weapon collision
	weaponCollider->OnComponentBeginOverlap.AddDynamic(this, &ABaseCharacter::OnOverlapBegin);
}

/// <summary>
///	Gets the character type as a string instead of an enum
/// </summary>
FName ABaseCharacter::GetCharacterTypeAsString()
{
	switch(characterType)
	{
		case ECharacterType::SKELETON:
			return FName(TEXT("Skeleton"));
		case ECharacterType::MALE_PLAYER:
			return FName(TEXT("MalePlayer"));
		case ECharacterType::FEMALE_PLAYER:
			return FName(TEXT("FemalePlayer"));
		default:
			return FName(TEXT(""));
	}
}



// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	// Ensure we are alive before updating anything
	if(characterState == ECharacterState::DEAD) return;

	
	Super::Tick(DeltaTime);
}

/// <summary>
/// Takes away the damage points from the characters health & than checks if the character is still alive
/// If the character isn't it will stop the actor from ticking, set the state to dead & trigger the death animation
/// </summary>
/// <param name="damagePoints">How many points to take from the character</param>
void ABaseCharacter::CharacterTakeDamage(float damagePoints)
{
	if(damagePoints > 0)
	{
		// TODO: If there is armour than maybe reduce the damage points applied
		currentHealth -= damagePoints;			// Reduce the damage points
		if(currentHealth <= 0.1)
		{
			SetCharacterState(ECharacterState::DEAD);		// Changes the state & allows for the animation instance to call the death animation
			PrimaryActorTick.bCanEverTick = false;			// Prevent the actor from ticking each frame
			GetCharacterMovement()->DisableMovement();			// Stops the character from moving

			// If this base character is AI
			if(auto chara = Cast<AAICharacter>(this))
			{
				chara->DropCoin();				// Drop the coin

				if(waveController != nullptr)
				{
					waveController->ReduceEnemies();
				}

				chara->ChangeState(EAIState::AI_DEAD);			// Change the state to dead
			}
			else if (auto player = Cast<APlayerCharacter>(this))
			{
				// If this character is the player we want to end the game
				UGameplayStatics::OpenLevel(GetWorld(), FName("Game_Over"));
			}

			// This timer will remove the dead enemies
			GetWorld()->GetTimerManager().SetTimer(destroyTimer, this, &ABaseCharacter::RemoveCharacter, destroyWaitTime, false);
		}
	}
}

/// <summary>
/// Called once the player has been setup
/// It will load all the details from a datatable & allows us to randomise a few different things
/// </summary>
/// <param name="character">The type of character</param>
void ABaseCharacter::SetupCharacter(const ECharacterType character)
{

	this->characterType = characterType;			// Set the character type
	// Ensure that we have a data table assign to load the character from
	if(characterDataTable != nullptr)
	{
		// Create a context string for logging
		static const FString ContextString(TEXT("Character Data Table"));
		
		// find the row of the characters type, if it's not found a warning will be printed in the console.
		FCharacterDataTable* character_data_table = characterDataTable->FindRow<FCharacterDataTable>(
			GetCharacterTypeAsString(), ContextString, true);

		// Make sure that the data table is valid
		if(character_data_table != nullptr)
		{
			// Make sure the mesh is not null & assign it the characters mesh
			if(const auto& mesh = character_data_table->CharacterMesh)
			{
				GetMesh()->SetSkeletalMesh(mesh);				// Set the mesh of the character
				characterName = FName(character_data_table->CharacterName);// Set the name of the character
				attackPoints = character_data_table->AttackPoints;			// Set the attack points of the character
				maxHealth = character_data_table->MaxHealth;				// Set the max health of the character
				currentHealth = maxHealth;									// Set the current health to be the max
				characterAnim = GetMesh()->GetAnimInstance();				// Get the anim instance
				Tags.Add(characterName);			// Add the character name as a tag
				Tags.Add("TakesDamage");
				characterCoins = character_data_table->CharacterCoins;			// Set the coins for the character

				// Load the animation data
				LoadAnimations(*character_data_table);
				// Load the weapon mesh
				LoadWeaponMesh(*character_data_table);
				// Load all the audio files
				LoadAudioData(*character_data_table);
				// Load the accessories
				LoadAccessories(*character_data_table);
			}
		}
	}		
}

/// <summary>
///	Handles loading of all the animation data
/// </summary>
/// <param name="dataTable">Data Table to load everything from</param>
void ABaseCharacter::LoadAnimations(FCharacterDataTable& dataTable)
{
	// Make sure we assigned an anim blueprint
	if(dataTable.AnimBlueprint != nullptr)
	{
		// Set the anim class for the character based on the data table
		GetMesh()->SetAnimInstanceClass(dataTable.AnimBlueprint);
		// set the character animation instance property
		characterAnim = GetMesh()->GetAnimInstance();
		// Cast the anim to the character anim so that we can set the owner
		if(auto* anim = Cast<UCharacterAnimInstance>(characterAnim))
		{
			// Set owner of the animation instance
			anim->SetOwner(this);
			// Set the animation montage
			anim->SetMontageDataTable(dataTable.AnimationDataTable);
		}			
	} else
	{
		// If there are any errors and we are in engine, print a message otherwise if we're not in engine
		// Quit the game
		if(GEngine)
		{
			UE_LOG(LogTemp, Error, TEXT("Mesh not assigned in data table"));
		} else
		{
			UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
		}
	}
}

void ABaseCharacter::LoadWeaponMesh(FCharacterDataTable& dataTable)
{
	weaponMesh->SetStaticMesh(dataTable.WeaponMesh);
}


/// <summary>
///	Handles loading of the audio data table
/// </summary>
/// <param name="dataTable">The character data table</param>
void ABaseCharacter::LoadAudioData(FCharacterDataTable& dataTable)
{
	if(const auto audio_data = dataTable.AudioDataTable)
	{
		const static FString ContextString = FString(TEXT("Audio Data Table"));			// Context Error String
		audio_data->GetAllRows(ContextString, audioData);			// Add all data to the array
	}
}

void ABaseCharacter::LoadAccessories(FCharacterDataTable& dataTable)
{
	// Get the accessories in an array
	TArray<FCharacterAccessiories> accessories = dataTable.accessories;
	// Check that we have accessories to apply
	if (accessories.Num() > 0)
	{
		// Loop through each accessories
		for (auto& a : accessories)
		{
			// Get the location & rotation of the object
			auto location = a.location;
			auto rotation = a.rotation;
			FActorSpawnParameters spawnParams;

			
			if (auto spawn = GetWorld()->SpawnActor<ACharacterAccessory>(location, rotation, spawnParams))
			{
				// Attach the object to the actor
				spawn->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, a.SocketName);

				// Cast the spawn to an accessory & Set the mesh
				if (ACharacterAccessory* accessory = Cast<ACharacterAccessory>(spawn))
				{
					accessory->SetMesh(a.AccMesh);
				}
			}
		}
	}
}

/// <summary>
///	Handles the sword overlapping an object
/// </summary>
void ABaseCharacter::OnOverlapBegin(UPrimitiveComponent* component, AActor* otherActor, UPrimitiveComponent* otherComp,
	int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Make sure we are attacking, have a weapon & not dead
	if(isAttacking && weaponMesh != nullptr && characterState != ECharacterState::DEAD)
	{
		// Make sure the actor we're attacking isn't this character & it has the correct tags
		if(otherActor->ActorHasTag("TakesDamage") && otherActor != Cast<AActor>(this))
		{
			// Cast the character to the base character & deal Damage
			if(auto target = Cast<ABaseCharacter>(otherActor))
			{
				target->CharacterTakeDamage(attackPoints);
			}

			// TODO: Attack Tower
		}
	}
}

/// <summary>
///	Will select a random audio track from the array and return it
/// </summary>
/// <param name="category">Category of audio we want to play</param>
USoundBase* ABaseCharacter::GetRandomAudio(EAudioCategory category)
{
	// Make sure the list isn't empty
	if(audioData.Num() > 0)
	{
		TArray<USoundBase*> audioList;			// define the array to store the potenial audio tracks

		// Loop through each audio in the array 
		for(auto audio : audioData)
		{
			// If the audio is for the category stated than add it to the list
			if(audio->AudioCategory == category)
			{
				audioList.Add(audio->SoundFile);
			}
		}

		int randomValue;			// Define an int to store the index we wish to select

		// Set the value & loop while it isn't within range of the array
		do
		{
			randomValue = FMath::RandRange(0, audioList.Num() - 1);
		} while(randomValue >= audioList.Num());

		// Return the audio track
		return audioList[randomValue];
	}

	return nullptr;
}

/// <summary>
///	Triggers an attack animation & will enable the colliders on the weapon
/// </summary>
void ABaseCharacter::Attack()
{
	if(!isAttacking)
	{
		//	Cast our anim instance to the character anim instnace & call the montage we want to play
		if(const auto animation = Cast<UCharacterAnimInstance>(characterAnim))
		{
			animation->PlayAnimMontage(EAnimationCategory::Attack);			// Triggering Attack 1 as the character only has 1 attack
		}
	}
}

/// <summary>
///	Handles playing of audio on the Audio Component
/// </summary>
void ABaseCharacter::PlayAudio(USoundBase* audio) const
{
	if(audioComponent != nullptr && audio != nullptr)
	{
		audioComponent->SetSound(audio);			// Set the sound we want to play
		audioComponent->Play();						// Play the audio
	}
}

/// <summary>
///	Called when we start an attack to enable collisions & prevent movement/Spamming
/// </summary>
void ABaseCharacter::StartAttack()
{
	isAttacking = true;			// Set attacking to true to prevent spamming
	weaponCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);			// Enable collisions
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);					// Disable movement on attack
}

/// <summary>
///	Called when finished attack to allow movement & disable weapon collision
/// </summary>
void ABaseCharacter::FinishAttack()
{
	isAttacking = false;				// Set attacking to false so we can attack again
	weaponCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);			// Disable collision on the weapon
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);					// Enable movement again
}

void ABaseCharacter::RemoveCharacter()
{
	GetMesh()->SetCollisionProfileName("OverlapAll");
	GetCapsuleComponent()->SetCollisionProfileName("OverlapAll");
	Destroy(true, true);
}

