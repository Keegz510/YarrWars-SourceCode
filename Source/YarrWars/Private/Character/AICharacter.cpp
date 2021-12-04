// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "AI/BaseAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Character/PathPoint.h"
#include "Controllers/QuartersController.h"
#include "PickUpItems/Coin.h"
#include "Towers/BaseTower.h"


AAICharacter::AAICharacter() : ABaseCharacter()
{
	characterMesh = GetMesh();			// Get the characters mesh
}

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> quartersList;			// Temp array to store all actors found
	// Find all actors of the quarters class
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AQuartersController::StaticClass(), quartersList);
	
	// If the first element isn't null than assign it to the quarters
	if(quartersList.Num() > 0)
	{
		if(quartersList[0] != nullptr)
		{
			captainQuarters = Cast<AQuartersController>(quartersList[0]);
		}
	}
	
}

void AAICharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}


void AAICharacter::SetupCharacter(const ECharacterType character)
{
	Super::SetupCharacter(character);

	// Determine what this AI will be doing during this wave.
	GenerateAIState();
	if(auto* contr = Cast<ABaseAIController>(GetController()))
	{
		contr->SetCharacterType(characterType);
	}
}

void AAICharacter::Attack()
{
	Super::Attack();

	if(target != nullptr)
	{
		if(aiState == EAIState::ATTACK_TOWER || aiState == EAIState::ATTACK_PLAYER)
		{
			if(auto castTarget = Cast<ABaseCharacter>(target))
			{
				castTarget->CharacterTakeDamage(attackPoints);
			}
			else if (auto tower = Cast<ABaseTower>(target))
			{
				tower->TowerTakeDamage(attackPoints);
			}
		}
	} else
	{
		// Make sure that we have assigned the quarters and deal damage to it
		if(captainQuarters != nullptr)
		{
			captainQuarters->QuartersTakeDamage(attackPoints, this);
		}
	}
}

void AAICharacter::DropCoin()
{
	if (coin != nullptr)
	{
		const FVector dropLocation = GetActorLocation();		// Location to drop
		const FRotator dropRotation = FRotator(0.0f, 0.0f, 0.0f);			// Zero out the rotation
		FActorSpawnParameters spawnParams;			// Spawning Parameters

		// spawn the coin and if it spawned correctly set the value of the coin
		if (auto spawned = GetWorld()->SpawnActor<ACoin>(coin, dropLocation, dropRotation, spawnParams))
		{
			spawned->SetCoinValue(characterCoins);
		}
	}

}


/// <summary>
///	Decides what the AI will be doing
/// </summary>
void AAICharacter::GenerateAIState()
{
	const int randValue = FMath::RandRange(0, 8);			// Generate a random number to select the state

	ABaseAIController* controller = Cast<ABaseAIController>(GetController());

	if(controller != nullptr)
	{
		// TODO REFACTOR: this may need to be changed depending on the amount of enemies that are on the ship at once
		// Determine the state based on the random value (6 in 8 chances of a path)
		switch(randValue)
		{
		case 0:		// Follow a path
			aiState = EAIState::PATH_POINT;
			FindPathPoint();// Assign a path point
			break;
		case 1:		// Find & attack a tower
			aiState = EAIState::ATTACK_TOWER;
			FindTower();
			break;
		case 2:			// Find & attack the player
			aiState = EAIState::ATTACK_PLAYER;
			target = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
			controller->SetEnemyTarget(target);
			break;
		default:			// Find & follow a path point
			aiState = EAIState::PATH_POINT;
			FindPathPoint();
			break;
		}

		// Set the ai State
		controller->SetAiState(aiState);
	}
}

void AAICharacter::FindPathPoint()
{
	TArray<AActor*> points;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APathPoint::StaticClass(), points);

	// TODO REFACTOR: Select a random point in the index
	// Loop through each point
	for(auto& actor : points)
	{
		// Make sure that we cast to the path point class 
		if(auto path = Cast<APathPoint>(actor))
		{
			// If the path is free than assign this path to the character
			if(path->IsPointFree())
			{
				PathPoint = path;
				path->AssignCharacter(this);
				return;
			}
		}
	}

	// If we can't find what we need than regenerate the state for the AI
	GenerateAIState();
}

void AAICharacter::FindTower()
{
	TArray<AActor*> towers;			// Array to store the towers
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseTower::StaticClass(), towers);			// Get an array of the towers

	// Ensure that we have towers before finding one
	if (towers.Num() > 0)
	{
		const int32 randTowerIndex = FMath::RandRange(0, (towers.Num() - 1));			// Select a random tower

		target = towers[randTowerIndex];			// Set the tower as a target
		if (auto contr = Cast<ABaseAIController>(GetController()))
		{
			contr->SetEnemyTarget(target);
			return;
		}

	}
	// If we can't find what we need than regenerate the state for the AI
	GenerateAIState();
}

void AAICharacter::TriggerGenerateStateTimer()
{
	GetWorld()->GetTimerManager().SetTimer(generatePathTimer, this, &AAICharacter::GenerateAIState, 3.0f, false);
}

/// <summary>
///	Sets the state of the AI Character
/// </summary>
void AAICharacter::ChangeState(const EAIState newState)
{
	aiState = newState;
	// Get the controller & set the new state
	if(auto* contr = Cast<ABaseAIController>(GetController()))
	{
		contr->SetAiState(aiState);
	}
}
