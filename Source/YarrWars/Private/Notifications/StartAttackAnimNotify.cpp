// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifications/StartAttackAnimNotify.h"
#include "Character/BaseCharacter.h"

void UStartAttackAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{

	// Ensure we are using the base character & call the start attack method
	if(auto character = Cast<ABaseCharacter>(MeshComp->GetOwner()))
	{
		character->StartAttack();
	}
}
