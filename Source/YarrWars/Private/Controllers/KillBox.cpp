// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/KillBox.h"
#include "Components/BoxComponent.h"
#include "Character/BaseCharacter.h"

// Sets default values
AKillBox::AKillBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the object
	killBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Kill Box"));

	// Setup Root component
	RootComponent = killBox;
	// Setup Collision
	killBox->SetCollisionProfileName(TEXT("OverlapAll"));
	killBox->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void AKillBox::BeginPlay()
{
	Super::BeginPlay();
	
	killBox->OnComponentBeginOverlap.AddDynamic(this, &AKillBox::OnBeginOverlap);
}

// Called every frame
void AKillBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/// <summary>
/// Handles Killing of the characters
/// </summary>
/// <param name="component"></param>
/// <param name="otherActor"></param>
/// <param name="otherComp"></param>
/// <param name="otherBodyIndex"></param>
/// <param name="bFromSweep"></param>
/// <param name="SweepResult"></param>
void AKillBox::OnBeginOverlap(UPrimitiveComponent* component, AActor* otherActor, UPrimitiveComponent* otherComp,
	int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Purple, TEXT("Kill Box"));
	if (otherActor != this && otherActor->ActorHasTag("TakesDamage"))
	{
		if (auto character = Cast<ABaseCharacter>(otherActor))
		{
			character->CharacterTakeDamage(1000.0f);
		}
	}
}

