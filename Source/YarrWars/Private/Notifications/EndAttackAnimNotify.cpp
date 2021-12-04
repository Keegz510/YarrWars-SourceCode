// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifications/EndAttackAnimNotify.h"
#include "Character/BaseCharacter.h"
#include "Character/PlayerCharacter.h"

void UEndAttackAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{

	// Cast to a character to ensure the notify is on a character
	if(auto character = Cast<ABaseCharacter>(MeshComp->GetOwner()))
	{
		// Check if we are a player character, if we are than use their Finsih attack otherwise use the base character
		if (auto player = Cast<APlayerCharacter>(character))
		{
			player->FinishAttack();
		}
		else
		{
			character->FinishAttack();
		}
		
	}
}
