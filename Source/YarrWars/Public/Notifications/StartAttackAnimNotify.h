// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "StartAttackAnimNotify.generated.h"

/**
 * Created By: Keegan Miller
 * Last Edit By: Keegan Miller
 * Date Edited: 26/08/2021
 * Version 1.0
 * Description: Handles the start of the attack. It will enable the collisions & start timers on the character
 */
UCLASS()
class YARRWARS_API UStartAttackAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
