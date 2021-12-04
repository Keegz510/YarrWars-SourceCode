// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuartersController.generated.h"
/*
 * Last Edited By: Keegan Miller
 * Edit Date: 28/08/2021
 * Version 1.0
 * Description: Handles the health of the captain quarters
 */
UCLASS()
class YARRWARS_API AQuartersController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuartersController();

	/* METHODS */
	void QuartersTakeDamage(const float damage, const AActor* attackingActor);
	virtual void BeginPlay() override;
private:
	

	/* PROPERTIES */
	// How much health the quarters currently has
	float quartersHealth;

	// The max health that the quarters has
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	float quartersMaxHealth = 100.0f;

};
