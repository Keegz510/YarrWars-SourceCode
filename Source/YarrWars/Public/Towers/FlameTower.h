// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Towers/BaseTower.h"
#include "FlameTower.generated.h"

/**
 * Created By: Keegan Miller
 * Last Edit Date: 05/09/2021
 * Version 1.0
 * Description: Class to control the the flame thrower
 */

/* FORWARD DECLARATION */
class UCapsuleComponent;

UCLASS()
class YARRWARS_API AFlameTower : public ABaseTower
{
	GENERATED_BODY()
public:
	AFlameTower();
	virtual void BeginPlay() override;
private:

	/* METHODS */
	// Handles what happens when someone collides.
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* component, AActor* otherActor, UPrimitiveComponent* otherComp,
		int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/* PROPERTIES */
	// Collider for the flame tower
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components", meta=(AllowPrivateAccess="true"))
	UCapsuleComponent* flameCollider;
	// Damage Points applied when colliding
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(AllowPrivateAccess="true"))
	float damage;

	
};
