// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

/*
 * Created By: Keegan Miller
 * Last Edit By: Keegan Miller
 * Edited Date: 30.08.2021
 * Version: 1.0
 * Description: Holds a mesh for the coin and adds it to the players coin count on collision
 */

/* FORWARD DECLARATIONS */
class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class YARRWARS_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoin();

	int32 coinValue;
	// Sets the value of the coin
	FORCEINLINE void SetCoinValue(const int32 value) { coinValue = value; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Mesh for the coin
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* coinMesh;

	// Collider for the coin
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	UBoxComponent* coinCollider;

	// When something overlaps the coin
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* component, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex,
    		bool bFromSweep, const FHitResult& SweepResult);
	
	

};
