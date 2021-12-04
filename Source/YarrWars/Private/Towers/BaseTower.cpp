// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers/BaseTower.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ABaseTower::ABaseTower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	towerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Tower Mesh"));			// Create the tower mesh
}

/// <summary>
/// Applys damage to the tower
/// </summary>
/// <param name="damage">Damage to be applied</param>
void ABaseTower::TowerTakeDamage(const float damage)
{
	// Ensure we are applying damage
	if (damage > 0)
	{
		currentHealth -= damage;				// Reduce the damage

		// If there is no health left destroy the tower
		if (currentHealth <= 0)
		{
			// TODO: Blow up Tower
			//Destroy(this);				// Destroy the tower
		}
	}
}

// Called when the game starts or when spawned
void ABaseTower::BeginPlay()
{
	Super::BeginPlay();
	currentHealth = maxHealth;				// Assign the current health to be max on load
}
