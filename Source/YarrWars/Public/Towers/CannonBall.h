// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CannonBall.generated.h"



/*
 * Created By: Keegan Miller
 * Last Edit by: Keegan Miller
 * Edit Date: 04/09/2021
 * Version: 1.0
 * Description: This class handles the cannon ball movement & collisions
 */

/* FORWARD DDECLARATION */
class UStaticMeshComponent;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class YARRWARS_API ACannonBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACannonBall();

	/* METHODS */
	// Fires the projectile
	void FireProjectile(const FVector fireDirection);

	/* PROPERTIES */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement Settings")
	float InitialSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement Settings")
	float maxSpeed;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	/* METHODS */
	// Handles what to do when we hit something
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* component, AActor* otherActor, UPrimitiveComponent* otherComp,
			int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	/* PROPERTIES */
	// Mesh for the cannon ball
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* ballMesh;

	// Collider for the ball
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh", meta=(AllowPrivateAccess="true"))
	USphereComponent* ballCollider;

	// Movement component to handle the projectile
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components", meta=(AllowPrivateAccess="true"))
	UProjectileMovementComponent* movementComponent;

	// How much damage is applied when hit a character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(AllowPrivateAccess="true"))
	float damagePerBall;
};
