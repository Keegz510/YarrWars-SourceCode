// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifications/PlayFootstepsAnimNotify.h"
#include "Character/BaseCharacter.h"

void UPlayFootstepsAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(auto character = Cast<ABaseCharacter>(MeshComp->GetOwner()))
	{
		//character->PlayAudio(character->GetRandomFootstepAudio());
	}
}
