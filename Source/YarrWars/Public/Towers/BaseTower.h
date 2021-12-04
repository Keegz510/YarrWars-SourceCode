// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BaseTower.generated.h"

/*
 * Created By: Keegan Miller
 * Last Edit By: Keegan Miller
 * Edit Date: 04/09/2021
 * Version: 1.0
 * Description: Base Tower used to spawn the data
 */

/* FORWARD DECLARATIONS */
class USkeletalMeshComponent;
class USkeletalMesh;

UCLASS()
class YARRWARS_API ABaseTower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseTower();

	void TowerTakeDamage(const float damage);

	FORCEINLINE USkeletalMesh* GetMesh() const { return towerMeshOnly; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Name of the tower
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tower Details", meta=(AllowPrivateAccess="true"))
	FString towerName;
	// What does the tower do?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tower Details", meta=(AllowPrivateAccess="true"))
	FText towerDescription;
	// How much gold the player needs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tower Details", meta=(AllowPrivateAccess="true"))
	int32 towerCost;
	
	// Mesh of the weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh", meta=(AllowPrivateAccess="true"))
	USkeletalMeshComponent* towerMesh;
	// Mesh used to view the placing item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh", meta=(AllowPrivateAccess="true"))
	USkeletalMesh* towerMeshOnly;
	// Health stats for the tower
	float currentHealth;
	const float maxHealth = 100;

};
