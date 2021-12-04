// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers/FlameTower.h"
#include "Components/CapsuleComponent.h"
#include "Character/AICharacter.h"

AFlameTower::AFlameTower()
{
	towerName = "Rum Powered Flame Thower";

	flameCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Flame Collision"));

	// Setup Collision
	flameCollider->SetCollisionProfileName("OverlapAll");
	flameCollider->SetGenerateOverlapEvents(true);
	// Attach to the mesh at the socket
	flameCollider->SetupAttachment(towerMesh, FName("VFX_Socket"));
}

void AFlameTower::BeginPlay()
{
	Super::BeginPlay();

	// Setup the collision on the capsule component
	flameCollider->OnComponentBeginOverlap.AddDynamic(this, &AFlameTower::OnBeginOverlap);
}


/// <summary>
/// On Overlap check if it's a character & apply damage
/// </summary>
void AFlameTower::OnBeginOverlap(UPrimitiveComponent* component, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (otherActor != this && otherActor->ActorHasTag("TakesDamage"))
	{
		if (auto character = Cast<AAICharacter>(otherActor))
		{
			character->CharacterTakeDamage(damage);
		}
	}
}
