// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BuildingSystem.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Character//PlayerCharacter.h"

// Sets default values
ABuildingSystem::ABuildingSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create the objects
	buildingBounds = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Building Bounds"));
	boundsCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider Bounds"));
	
	// Set the profile name to overlap all so we can walk through it
	buildingBounds->SetCollisionProfileName(TEXT("OverlapAll"));
	boundsCollider->SetCollisionProfileName(TEXT("OverlapAll"));
	// Allow Generation of overlap events
	boundsCollider->SetGenerateOverlapEvents(true);
	buildingBounds->SetGenerateOverlapEvents(true);
	
}

// Called when the game starts or when spawned
void ABuildingSystem::BeginPlay()
{
	Super::BeginPlay();

	ToggleBuildMode(false);		// Set build mode to false

	// Set the collision delegates for the box component
	boundsCollider->OnComponentBeginOverlap.AddDynamic(this, &ABuildingSystem::OnComponentBeginOverlap);
	boundsCollider->OnComponentEndOverlap.AddDynamic(this, &ABuildingSystem::OnComponentEndOverlap);
	
}

/// <summary>
///	When component begins overlap check if it's a player & toggle can build
/// </summary>
void ABuildingSystem::OnComponentBeginOverlap(UPrimitiveComponent* component, AActor* otherActor, UPrimitiveComponent* otherComp,
	int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Buliding Collisions"));
	if(auto player = Cast<APlayerCharacter>(otherActor))	
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Building Allowed"));
		canBuild = true;
	}
}

/// <summary>
///	When the component leaves the overlap if it's the player than toggle can build
/// </summary>
void ABuildingSystem::OnComponentEndOverlap(UPrimitiveComponent* component, AActor* otherActor, UPrimitiveComponent* otherComp,
	int32 otherBodyIndex)
{
	if(auto player = Cast<APlayerCharacter>(otherActor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Building Not Allowed"));
		canBuild = false;
	}
}

// Called every frame
void ABuildingSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	canBuild = true;				// TODO: Remove Hacked Code (This allow building placement anywhere)
}

/// <summary>
/// Sets the building mode & toggles the visibiliy of the bounds
/// </summary>
void ABuildingSystem::ToggleBuildMode(const bool mode)
{
	isBuilding = mode;
	buildingBounds->SetVisibility(mode);
}

USkeletalMesh* ABuildingSystem::SetPlacingObject(const int32 index)
{
	if(index < towers.Num())
	{
		placingTower = towers[index];
		if(placingTower != nullptr)
		{
			return buildingMeshes[index];
		}
	}

	return nullptr;
}

void ABuildingSystem::PlaceTower(APlayerCharacter* player)
{
	// If we can build and we are building
	if (canBuild && isBuilding)
	{
		// Make sure we have a tower to place & the player passing through is valid
		if (placingTower != nullptr && player != nullptr)
		{
			
			FVector location = player->GetActorLocation();
			FRotator rotation = FRotator(0.0f, 180.0f, 0.0f);

			FActorSpawnParameters spawnParams;
			if (auto spawned = GetWorld()->SpawnActor<ABaseTower>(placingTower, location, rotation, spawnParams))
			{
				UE_LOG(LogTemp, Warning, TEXT("Spawned Tower"));
			}
		}
	}
	
}

void ABuildingSystem::PlaceTower(FVector location, FRotator rotation)
{
//	if (canBuild && isBuilding)
//	{
		if (placingTower != nullptr)
		{
			FActorSpawnParameters spawnParams;
			if (auto spawned = GetWorld()->SpawnActor<ABaseTower>(placingTower, location, rotation, spawnParams))
			{
				spawned->SetActorRotation(rotation);
				UE_LOG(LogTemp, Warning, TEXT("Spawned Tower"));
			}
		}
	//}
}

