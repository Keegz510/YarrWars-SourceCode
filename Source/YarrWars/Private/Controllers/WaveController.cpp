// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/WaveController.h"
#include "Character/AICharacter.h"
#include "Character/BaseCharacter.h"
#include "Character/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UI/GameHUD.h"


// Sets default values
AWaveController::AWaveController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

void AWaveController::ReduceEnemies()
{
	enemiesAlive -= 1;
	
	if(enemiesAlive <= 0)
	{
		EndRound();
	} else
	{
		if(hud != nullptr)
			UpdateHUD();
	}
}

// Called when the game starts or when spawned
void AWaveController::BeginPlay()
{
	Super::BeginPlay();
	
	
	currentRound = 1;
	// Create a timer to spawn the enemies
	GetWorld()->GetTimerManager().SetTimer(endRoundTimer, this, &AWaveController::SpawnWave, roundWaitTime, false, -1);
}

/// <summary>
/// Handles spawning of the enemies each round
/// </summary>
void AWaveController::SpawnWave()
{
	UE_LOG(LogTemp, Warning, TEXT("spawning wave"));
	// Ensure we have spawn points in the scene
	if(spawnPoints.Num() > 0)
	{
		// Determine how many enemies to spawn
		const int enemiesToSpawn = enemiesPerRound[currentRound - 1];
		// Loop through the amount of enemies & spawn them
		for(int i = 0; i < enemiesToSpawn; ++i)
		{
			// Select a random spawn point from the array
			const FVector spawnLocation = GetActorLocation() + spawnPoints[FMath::RandRange(0, (spawnPoints.Num() - 1))];
			// Set the rotation
			const FRotator spawnRotation = FRotator::ZeroRotator;			// Set the rotation to zero

			// Set the spawn params to always spawm
			FActorSpawnParameters spawnParams;
			spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			
			// If we have spawned the actor than set it up
			if(auto enemy = GetWorld()->SpawnActor<AAICharacter>(spawnClass, spawnLocation, spawnRotation, spawnParams))
			{
				// Setup the character to be a skeleton
				enemy->SetupCharacter(ECharacterType::SKELETON);			// Set the character
				enemiesAlive += 1;			// Increase the enemies alive
			}
		}
		if(hud != nullptr)
		{
			UpdateHUD();
		} else
		{
			if(const auto player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
			{
				hud = player->GetHUD();
				UpdateHUD();
			}
		}
		
	}
}

/// <summary>
/// Increases the round & than starts a timer to spawn
/// </summary>
void AWaveController::EndRound()
{

	currentRound += 1;			// Increase the round
	UpdateHUD();				// Update the HUD
	// If we have passed the max rounds then call game over
	if(currentRound > MAX_ROUNDS)
	{
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("Game_Over"));
	} else
	{
		// Otherwise start the timer
		GetWorld()->GetTimerManager().SetTimer(endRoundTimer, this, &AWaveController::SpawnWave, roundWaitTime, false, -1);
	}	
}

/// <summary>
/// Handles updating of the UI
/// </summary>
void AWaveController::UpdateHUD()
{
	// Set the integers into strings
	auto enemiesAliveAsText = FString::FromInt(enemiesAlive);
	auto currentRoundAsText = FString::FromInt(currentRound);

	FString st = "Round: " + currentRoundAsText + " | Enemies: " + enemiesAliveAsText;
	FText text = FText::FromString(st);				// Make it a string
	if(hud != nullptr)
		hud->UpdateTotalEnemies(text);				// Update the IU
	
}

// Called every frame
void AWaveController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

