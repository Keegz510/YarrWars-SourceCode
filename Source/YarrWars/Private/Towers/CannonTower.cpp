// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers/CannonTower.h"
#include "Towers/CannonBall.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimMontage.h"
#include "Components/SkeletalMeshComponent.h"
//#include "Niagara/Public/NiagaraFunctionLibrary.h"

ACannonTower::ACannonTower() : ABaseTower()
{
	towerName = "Cannon Tower";

	sfxComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SFX"));
	
}

void ACannonTower::BeginPlay()
{
	Super::BeginPlay();
	// Create a timer to that call the fire cannon method
	GetWorld()->GetTimerManager().SetTimer(fireTimer, this, &ACannonTower::FireCannon, fireWaitTime, true);
	sfxComponent->SetSound(fireAudio);
	
}

/// <summary>
/// Fires a projectile from the fire point
/// </summary>
void ACannonTower::FireCannon()
{
	// Set the location & rotation of the spawn
	const FVector spawnLocation = towerMesh->GetSocketLocation(FName("FirePoint"));
	const FRotator spawnRotation = FRotator::ZeroRotator;

	// Setup the spawn params
	FActorSpawnParameters spawnParans;
	spawnParans.Instigator = GetInstigator();
	spawnParans.Owner = this;

	// Attempt to spawn the projectile and if successful than fire the projectile
	if (ACannonBall* cannonBall = GetWorld()->SpawnActor<ACannonBall>(cannonProjectile, spawnLocation, spawnRotation, spawnParans))
	{
		cannonBall->FireProjectile(towerMesh->GetForwardVector());

		
		if (sfxComponent != nullptr)
		{
			sfxComponent->Play();
		}

		towerMesh->GetAnimInstance()->Montage_Play(fireMontage);
		TriggerEmiiter();
		
	}
}
