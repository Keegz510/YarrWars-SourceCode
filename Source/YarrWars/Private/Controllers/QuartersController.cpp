// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/QuartersController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AQuartersController::AQuartersController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AQuartersController::QuartersTakeDamage(const float damage, const AActor* attackingActor)
{
	// Make sure that the the player isn't dealing damage to the quarters
	if(!attackingActor->ActorHasTag("Male Player") || !attackingActor->ActorHasTag("Female Player"))
	{
		quartersHealth -= damage;			// Reduce the health
		// If the health is less than or equal to 0, it's game over
		if(quartersHealth <= 0)
		{
			UGameplayStatics::OpenLevel(this, FName(TEXT("Game_Over")));
		}
	}
}

void AQuartersController::BeginPlay()
{
	quartersHealth = quartersMaxHealth;
}

