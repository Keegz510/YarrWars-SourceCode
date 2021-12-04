// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "PlayFootstepsAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class YARRWARS_API UPlayFootstepsAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
	UPlayFootstepsAnimNotify() {}

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
