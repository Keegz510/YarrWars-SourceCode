// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Character/CharacterAnimInstance.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UI/GameHUD.h"
#include "Controllers/BuildingSystem.h"

APlayerCharacter::APlayerCharacter() : ABaseCharacter()
{

	// Prevent Rotating
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;			// Move in the direction of the input
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 440.0f, 0.0f);			// Set the rate we rotate the character at 

	// TODO: Implement Jumping

	// Setup the camera & spring arm
	SetupSpringArm();
	SetupCamera();

	placingTowerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Placing Tower"));
	placingTowerMesh->SetupAttachment(GetMesh());

	
	
}

/// <summary>
/// Called when the class enters into the game
/// </summary>
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetupHUD();
	FindBuildingAreas();
}

/// <summary>
///	Called every frame
/// </summary>
void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APlayerCharacter::AddCoin(const int coin)
{
	characterCoins += coin;
	if(gameHUD != nullptr)
	{
		gameHUD->UpdateTotal(characterCoins);
	}
}


/// <summary>
/// Allows for user input
/// </summary>
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/* AXIS BINDING */
	{
		// Movement Axis
		PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

		// Look Axis
		PlayerInputComponent->BindAxis("LookUp", this, &ABaseCharacter::AddControllerPitchInput);
		PlayerInputComponent->BindAxis("Turn", this, &ABaseCharacter::AddControllerYawInput);

		// Tower Rotation
		PlayerInputComponent->BindAxis("RotateTower", this, &APlayerCharacter::RotateTower);
	}
	
	/* BUTTON BINDING */
	{
		// Trigger Player Attack
		PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::Attack);

		// Actions

		// Toggle Building System
		PlayerInputComponent->BindAction("EquipWeapon", IE_Pressed, this, &APlayerCharacter::ToggleSword);
		PlayerInputComponent->BindAction("CannonTower", IE_Pressed, this, &APlayerCharacter::SetCannonTower);
		PlayerInputComponent->BindAction("FlameTower", IE_Pressed, this, &APlayerCharacter::SetFlameTower);

		PlayerInputComponent->BindAction("ConfirmTowerPlacement", IE_Pressed, this, &APlayerCharacter::PlaceTower);
	}
}

/// <summary>
/// Creates & sets up the spring arm for the blueprint
/// </summary>
void APlayerCharacter::SetupSpringArm()
{
	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	cameraBoom->SetupAttachment(RootComponent);
	cameraBoom->bUsePawnControlRotation = true;
	cameraBoom->TargetArmLength = targetArmLength;
	cameraBoom->SetRelativeLocation(FVector(0.0f, 0.0f, BaseEyeHeight));
}

/// <summary>
/// Creates & sets up the camera component for the blueprint
/// </summary>
void APlayerCharacter::SetupCamera()
{
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	camera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName);
	camera->bUsePawnControlRotation = false;
}

/// <summary>
///	Allows the character to move Forward & Backwards
/// </summary>
void APlayerCharacter::MoveForward(const float value)
{
	// Ensure we have a controller attach to this character & we are attempting
	// to move before running applying movement
	if(Controller != nullptr && value != 0)
	{
		// Get the current rotation of the character
		const FRotator rotation = GetController()->GetControlRotation();		
		const FRotator desired_rotator = FRotator(0, rotation.Yaw, 0);

		// Get the forward vector of the character on the X axis
		const FVector forward_vector = FRotationMatrix(desired_rotator).GetScaledAxis(EAxis::X);

		// Apply the movement input
		AddMovementInput(forward_vector, value);
	} else
	{
		// If we don't have a controller attached than print an error message to the screen
		if(GEngine != nullptr && Controller == nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Controller Not Attached"));
		}
	}
}

/// <summary>
///	Allows the character to move left & right
/// </summary>
void APlayerCharacter::MoveRight(const float value)
{
	// Ensure we have a controller attach to this character & we are attempting
	// to move before running applying movement
	if(Controller != nullptr && value != 0)
	{
		// Get the current rotation of the character
		const FRotator rotation = GetController()->GetControlRotation();		
		const FRotator desired_rotator = FRotator(0, rotation.Yaw, 0);

		// Get the forward vector of the character on the Y axis
		const FVector forward_vector = FRotationMatrix(desired_rotator).GetScaledAxis(EAxis::Y);

		// Apply the movement input
		AddMovementInput(forward_vector, value);
	} else
	{
		// If we don't have a controller attached than print an error message to the screen
		if(GEngine != nullptr && Controller == nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Controller Not Attached"));
		}
	}
}


/// <summary>
/// Adds the HUD to the scene
/// </summary>
void APlayerCharacter::SetupHUD()
{

	// Handles loading of the HUD
	FString hudPath = TEXT("WidgetBlueprint'/Game/UI_Widgets/BP_GameHUD.BP_GameHUD'");
	UBlueprint* hudBP = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), NULL, *hudPath));

	if (hudBP != nullptr)
	{
		playerHUD_Widget = hudBP->GeneratedClass;
	}

	// Make sure we have assigned the player HUD
	if(playerHUD_Widget != nullptr)
	{
		// Create the hud & ensure it's not null than add it to the viewport & set it up
		playerHUD = CreateWidget(GetWorld(), playerHUD_Widget);
		if(playerHUD != nullptr)
		{
			playerHUD->AddToViewport();
			// Cast the widget to gameHUD and setup the variables
			gameHUD = Cast<UGameHUD>(playerHUD);
			if(gameHUD != nullptr)
			{
				gameHUD->UpdateTotal(characterCoins);
				gameHUD->UpdateHealth(currentHealth);
			}
		}
	}
	

	// TODO: Load HUD
}


/// <summary>
/// Finds all the building areas in the current scene
/// </summary>
void APlayerCharacter::FindBuildingAreas()
{
	TArray<AActor*> temp;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABuildingSystem::StaticClass(), temp);

	// Ensure we have elements in the array
	if(temp.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Got Objects"));
		// Loop through the array & cast to a building system
		for(int i = 0; i < temp.Num(); ++i)
		{
			// If successful add the building area to the array
			if(ABuildingSystem* area = Cast<ABuildingSystem>(temp[i]))
			{
				UE_LOG(LogTemp, Warning, TEXT("Adding Building System"));
				buildingAreas.Add(area);

				UE_LOG(LogTemp, Warning, TEXT("Added System"));
			}
		}
	}
}

/// <summary>
/// Sets the tower cannon as the placing object
/// </summary>
void APlayerCharacter::SetCannonTower()
{
	AllowRotation(true);				// Allow the rotation
	for(auto b : buildingAreas)
	{
		if(b != nullptr)
		{
			canAttack = false;
			USkeletalMesh* mesh = b->SetPlacingObject(0);
			if (mesh != nullptr)
			{
				placingTowerMesh->SetSkeletalMesh(mesh);
			}
				

			b->ToggleBuildMode(true);
			
		}
	}
}

/// <summary>
/// Set the flame tower as the placing object
/// </summary>
void APlayerCharacter::SetFlameTower()
{
	AllowRotation(true);
	for(auto b : buildingAreas)
	{
		if(b != nullptr)
		{
			canAttack = false;
			USkeletalMesh* mesh = b->SetPlacingObject(1);
			if (mesh != nullptr)
			{
				placingTowerMesh->SetSkeletalMesh(mesh);
			}
			b->ToggleBuildMode(true);
		}
	}
}

/// <summary>
/// Stops us from building
/// </summary>
void APlayerCharacter::ToggleSword()
{
	AllowRotation(false);
	for(auto& b : buildingAreas)
	{
		if(b != nullptr)
		{
			canAttack = true;
			placingTowerMesh->SetSkeletalMesh(nullptr);
			b->ToggleBuildMode(false);
			
		}
	}
}

/// <summary>
/// Handles placing of the towers in the area that we are in
/// </summary>
void APlayerCharacter::PlaceTower()
{
	// Make sure the character isn't attacking
	if (!canAttack)
	{
		// Loop through all the areas in the scene
		for (auto areas : buildingAreas)
		{
			// if the player is in the area & can build
			if (areas->CanBuild())
			{
				// Get the location to allow tower rotation
				const FVector location = placingTowerMesh->GetComponentLocation();

				// Create the rotation for the placement of the tower
				const FRotator placementRotation(
					(GetActorRotation().Pitch + towerRotation.Pitch),
					(GetActorRotation().Yaw + towerRotation.Yaw),
					(GetActorRotation().Roll + towerRotation.Roll)
				);
				// Place the tower
				areas->PlaceTower(location, placementRotation);
				// Reset the tower rotation
				towerRotation = FRotator(0, 0, 0);
				// Toggle the sword
				ToggleSword();

				return;
			}
		}
	}
}

/// <summary>
/// Handles rotating the tower on the yaw
/// </summary>
/// <param name="value"></param>
void APlayerCharacter::RotateTower(const float value)
{
	if (!canAttack && value != 0)
	{
		// Get the rotation
		FRotator currentRotation = placingTowerMesh->GetRelativeRotation();
		// Create the new rotation
		const FRotator newRotation(currentRotation.Roll, (currentRotation.Yaw), (currentRotation.Yaw + value));
		// Set the rotation of the tower
		placingTowerMesh->AddRelativeRotation(newRotation);
	}
}


/// <summary>
/// Allows the player to rotate on the spot
/// </summary>
/// <param name="allow">If we want to rotate or not</param>
void APlayerCharacter::AllowRotation(const bool allow)
{
	//bUseControllerRotationPitch = allow;
	bUseControllerRotationRoll = allow;
	bUseControllerRotationYaw = allow;
}

/// <summary>
/// Handles the player attack
/// </summary>
void APlayerCharacter::Attack()
{
	// Check that the player can attack
	if (canAttack)
	{
		Super::Attack();	// Allow for the base class attack
		canAttack = false;			// Stop the player from attacking
	}
}

/// <summary>
/// Handles finishing of the attack
/// </summary>
void APlayerCharacter::FinishAttack()
{
	Super::FinishAttack();				// Call finish attack on base class
	canAttack = true;				// Allow the player to attack
}


