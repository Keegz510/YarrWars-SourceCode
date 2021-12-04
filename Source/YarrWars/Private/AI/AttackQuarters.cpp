// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AttackQuarters.h"
#include "Character/BaseCharacter.h"
#include "Character/AICharacter.h"
#include "AI/BaseAIController.h"

EBTNodeResult::Type UAttackQuarters::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get the controller & character
	const auto controller = Cast<ABaseAIController>(OwnerComp.GetOwner());
	const auto character = Cast<AAICharacter>(controller->GetCharacter());

	// Make sure that they are valid
	if(controller != nullptr && character != nullptr)
	{
		character->Attack();			// Call attack on the character
		// TODO: Deal Damage to the quarters
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
	
}
