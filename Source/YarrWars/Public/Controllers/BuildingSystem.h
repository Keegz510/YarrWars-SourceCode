// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Towers/BaseTower.h"
#include "BuildingSystem.generated.h"


/*
 * Created By: Keegan Miller
 * Last Edit By: Keegan Miller
 * Last Edit Date: 03/09/2021
 * Version: 1.0
 * Description: Main actor for the building system
 */

/* FORWARD DECLARATIONS */
class UStaticMeshComponent;
class USkeletalMeshComponent;
class USkeletalMesh;
class UBoxComponent;
class ABaseTower;
class APlayerCharacter;

UCLASS()
class YARRWARS_API ABuildingSystem : public AActor
{
	GENERATED_BODY()
	
public:
	/* CONSTRUCTORS */
	// Sets default values for this actor's properties
	ABuildingSystem();

	/* METHODS */
	// Called every frame
    virtual void Tick(float DeltaTime) override;
	// Set the if we are in building mode
	void ToggleBuildMode(const bool mode);
	// Sets the object as placing object
	USkeletalMesh* SetPlacingObject(const int32 index);

	// If the player can build in the array they are in
	FORCEINLINE bool CanBuild() const { return canBuild; }

	// Handles spawning the tower into the world
	void PlaceTower(APlayerCharacter* player);
	// Place tower at a specific location
	void PlaceTower(FVector location, FRotator rotation = FRotator(0.0f, 0.0f, 0.0f));
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	/* METHODS */
	// When something enters into the building area
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* component, AActor* otherActor, UPrimitiveComponent* otherComp,
                                 	int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// When something leaves the building area
	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* component, AActor* otherActor, UPrimitiveComponent* otherComp,
                               	int32 otherBodyIndex);

	/* PROPERTIES */
	// Where to place the mesh in the world
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* buildingBounds;

	// Box component to detect a trigger
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh", meta=(AllowPrivateAccess="true"))
	UBoxComponent* boundsCollider;
	// List of towers that we can place
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Towers", meta=(AllowPrivateAccess="true"))
	TArray<TSubclassOf<ABaseTower>> towers;
	// List of the meshes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Towers", meta=(AllowPrivateAccess="true"))
	TArray<USkeletalMesh*> buildingMeshes;
	
	bool isBuilding = false;			// Property to determine if the player is building
	bool canBuild = false;				// If the player can build an object

	// Subclass of the base tower
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Towers", meta=(AllowPrivateAccess="true"))
	TSubclassOf<ABaseTower> placingTower;			// What tower the player has selected to build

	
};


