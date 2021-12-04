// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterAccessory.generated.h"

UCLASS()
class YARRWARS_API ACharacterAccessory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACharacterAccessory();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* AccessoryMesh;

	// Set the static mesh component
	inline void SetMesh(class UStaticMesh* mesh) { AccessoryMesh->SetStaticMesh(mesh); }
	
	

};
