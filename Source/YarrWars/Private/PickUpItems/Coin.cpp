// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpItems/Coin.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Character/BaseCharacter.h"
#include "Character/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

	// Setup the static mesh
	coinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("COIN"));
	coinMesh->SetupAttachment(RootComponent);
	// Setup coin collision
	coinMesh->SetGenerateOverlapEvents(true);
	coinMesh->SetCollisionProfileName("OverlapAll");
	
	coinMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	// Create the collider
	coinCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("COLLIDER"));
	coinCollider->SetupAttachment(coinMesh);
	// Set collider collision
	coinCollider->SetCollisionProfileName("OverlapAll");			// Set the name of the collision profile to overlap all to get all events
	coinCollider->SetGenerateOverlapEvents(true);
	coinMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
	// Add overlap event to the coin collider
	coinCollider->OnComponentBeginOverlap.AddDynamic(this, &ACoin::ACoin::OnOverlapBegin);
}

void ACoin::OnOverlapBegin(UPrimitiveComponent* component, AActor* otherActor, UPrimitiveComponent* otherComp,
	int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Ensure just the character has overlapped the collider
	if(otherActor->ActorHasTag("Male Player") || otherActor->ActorHasTag("Female Player"))
	{
		// Cast to the player character & add the value of this coin
		if(auto player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
		{
			player->AddCoin(coinValue);
		}
		coinCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		coinMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Destroy(true, true);			// Destroy the coin
	}
}
