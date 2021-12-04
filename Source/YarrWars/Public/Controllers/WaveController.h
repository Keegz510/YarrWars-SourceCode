// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveController.generated.h"

/*
 * Edit By: Keegan Miller
 * Last Edit Date: 31/08/2021
 * Version 1.0
 * Description: Handles spawning of the enemies and timers between rounds
 */

/* FORWARD DECLARATIONS */
class UGameHUD;
class AAICharacter;


#define MAX_ROUNDS 5

UCLASS()
class YARRWARS_API AWaveController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveController();

	public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Returns the round we are currently in
	FORCEINLINE int32 GetCurrentRound() const { return currentRound; }
	// Returns how many enemies are currently alive
	FORCEINLINE int32 GetEnemiesAlive() const { return enemiesAlive; }
	// Reduces the enemy alive count by 1
	void ReduceEnemies();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	/* METHODS */
	// Handles spawning of the enemies
	void SpawnWave();
	// Handles the end of the round & begins timer
	void EndRound();
	// Updates the players HUD
	void UpdateHUD();

	/* PROPERTIES */
	// Array to store each spawn point
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Points", meta=(AllowPrivateAccess="true", MakeEditWidget))
	TArray<FVector> spawnPoints;

	// Sub class to spawn for enemies
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Data", meta=(AllowPrivateAccess="true"))
	TSubclassOf<AAICharacter> spawnClass;

	// What round it currently is
	int32 currentRound;
	// Array to say how many enemies per each round
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Round Data", meta=(AllowPrivateAccess="true"))
	TArray<int32> enemiesPerRound;
	// How many enemies are currently in the round
	int32 enemiesAlive;

	// Called at the end of the round to determine when next spawn is
	FTimerHandle endRoundTimer;
	// How long we get inbetween rounds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Timers", meta=(AllowPrivateAccess="true"))
	float roundWaitTime;

	// Reference to the game hud
	UGameHUD* hud;

};
