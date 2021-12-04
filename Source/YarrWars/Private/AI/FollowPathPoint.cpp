// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/FollowPathPoint.h"
#include "AI/BaseAIController.h"
#include "Character/AICharacter.h"
#include "Character/PathPoint.h"

EBTNodeResult::Type UFollowPathPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get & make sure that the controller isn't null
	if(auto* aiController = Cast<ABaseAIController>(OwnerComp.GetOwner()))
	{
		// Get & make sure that the blackboard component isn't null
		if(auto* bbComp = aiController->GetBlackboard())
		{
			// Get & make sure that the character isn't null
			if(const auto* character = Cast<AAICharacter>(aiController->GetCharacter()))
			{
				// Make sure the path point isn't null
				if(character->PathPoint != nullptr)
				{
					// Add the actor location to the path point location to get the location we need to travel to
					const FVector path_point_location = character->PathPoint->GetActorLocation() += character->PathPoint->GetPointLocation();
					
					// set the target location on the blackboard
					aiController->SetTargetLocation(path_point_location);

					// Return that the task is successful
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}

	return EBTNodeResult::Failed;
}
