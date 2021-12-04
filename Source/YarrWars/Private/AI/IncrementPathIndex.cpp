// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/IncrementPathIndex.h"
#include "Character/AICharacter.h"
#include "AI/BaseAIController.h"
#include "Character/PathPoint.h"

EBTNodeResult::Type UIncrementPathIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get the character class & the controller class
	const auto* controller = Cast<ABaseAIController>(OwnerComp.GetOwner());
	const auto* character = Cast<AAICharacter>(controller->GetCharacter());

	// Make sure that the controller & character aren't null
	if(controller != nullptr && character != nullptr)
	{
		// Increment the path index & complete the task
		character->PathPoint->IncrementPath();
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
