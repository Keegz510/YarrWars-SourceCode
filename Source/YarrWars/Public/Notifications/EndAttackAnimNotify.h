// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndAttackAnimNotify.generated.h"

/**
 * Last Edit By: Keegan Miller
 * Date Edited: 26/08/2021
 * Version 1.0
 * Description: Called when can attack is finished
 */
UCLASS()
class YARRWARS_API UEndAttackAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
