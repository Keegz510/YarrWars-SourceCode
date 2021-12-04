// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Towers/BaseTower.h"
//#include "Niagara/Classes/NiagaraSystem.h"
#include "CannonTower.generated.h"

/**
 * Created By: Keegan Miller
 * Last Edit By: Keegan Miller
 * Edit Date: 04/09/2021
 * Version 1.0
 * Description: The cannon tower class handles the animation and the spawn.
 */

/* FORWARD DECLARATIONS */
class ACannonBall;
class UAudioComponent;
class UNiagaraSystem;
class UAnimMontage;

UCLASS()
class YARRWARS_API ACannonTower : public ABaseTower
{
	GENERATED_BODY()
public:
	ACannonTower();
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
		void TriggerEmiiter();
private:
	FTimerHandle fireTimer;				// Timer to handle when the cannon can fire

	UFUNCTION(BlueprintCallable)
	void FireCannon();

	

	// Time before it fires
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timers", meta = (AllowPrivateAccess = "true"))
		float fireWaitTime;

	// Plays the cannon shooting audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components", meta=(AllowPrivateAccess="true"))
	UAudioComponent* sfxComponent;
	// Audio to play
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components", meta=(AllowPrivateAccess="true"))
	USoundBase* fireAudio;

	// Component for the particle effects
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components", meta=(AllowPrivateAccess="true"))
	//UNiagaraSystem* vfxComponent;

	// Reference to fire montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components", meta=(AllowPrivateAccess="true"))
	UAnimMontage* fireMontage;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectile Settings", meta=(AllowPrivateAccess="true"))
	TSubclassOf<ACannonBall> cannonProjectile;
};
