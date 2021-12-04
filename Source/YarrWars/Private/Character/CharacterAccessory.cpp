// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterAccessory.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACharacterAccessory::ACharacterAccessory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the object & Make it root component
	AccessoryMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Accessory Mesh"));
	RootComponent = AccessoryMesh;

	// Setup the collision
	AccessoryMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AccessoryMesh->SetCollisionProfileName("NoCollision");
	AccessoryMesh->SetGenerateOverlapEvents(false);
}

