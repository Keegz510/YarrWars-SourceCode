// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BaseAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter.h"

ABaseAIController::ABaseAIController()
{
	behaviorTree = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behaviour Tree Component"));
	blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
}

/// <summary>
/// Called when the AI posses the character.
/// It will start the blackboard component & behavior tree
/// </summary>
/// <param name="InPawn">Pawn that is taking control of this controller</param>
void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	owner = Cast<AAICharacter>(InPawn);			// Cast the pawn that is possesing this controller to the AI Character Class

	// Ensure that the Character is valid before proceeding
	if(owner != nullptr)
	{
		// Initialize the blackboard
		if(owner->BehaviorTree->BlackboardAsset)
		{
			blackboard->InitializeBlackboard(*(owner->BehaviorTree->BlackboardAsset));
		}

		// Started the behavior tree
		behaviorTree->StartTree(*owner->BehaviorTree);
	}
	
}

/// <summary>
/// This method assigns the target we want to attack
/// </summary>
/// <param name="target">What we want to target</param>
void ABaseAIController::SetEnemyTarget(AActor* target) const
{
	// Ensure that the target is not null
	if(target != nullptr)
	{
		// Set the value as an object
		blackboard->SetValueAsObject(bbKeys.EnemyToTarget, target);
	}
}

/// <summary>
///	Sets the AI State on the blackboard
/// </summary>
/// <param name="state">State we want to set for the character</param>
void ABaseAIController::SetAiState(EAIState& state) const
{
	blackboard->SetValueAsEnum(bbKeys.AI_State, state);
}

/// <summary>
///	Sets the type of character it is on the blackboard
/// </summary>
/// <param name="type">The type of character this is</param>
void ABaseAIController::SetCharacterType(ECharacterType type) const
{
	blackboard->SetValueAsEnum(bbKeys.CharacterType, type);
}

void ABaseAIController::SetTargetLocation(FVector location) const
{
	blackboard->SetValueAsVector(bbKeys.TargetLocation, location);
}

void ABaseAIController::SetAttackWaitTime(float waitTime) const
{
	blackboard->SetValueAsFloat(bbKeys.AttackWaitTime, waitTime);
}	
