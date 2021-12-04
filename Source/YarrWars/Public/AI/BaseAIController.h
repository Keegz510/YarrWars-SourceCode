// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter.h"

#include "BaseAIController.generated.h"

/**
 * Created By: Keegan Miller
 * Last Edit By: Keegan Miller
 * Edit Date: 21/08/2021
 * Description: This class will handle the AI blackboards
 */

/* FORWARD DECLARATIONS */
class UBehaviorTreeComponent;
class UBlackboardComponent;
class AAICharacter;

/// <summary>
///	This class will be used to store the names of each blackboard key in a variable
///	Everything put into the blackboard as a key needs to be made a variable so that we aren't typing out strings
/// </summary>
USTRUCT()
struct FBlackboardKeys
{
	GENERATED_BODY()
public:
	FBlackboardKeys()
	{
		TargetLocation = FName(TEXT("TargetLocation"));
		EnemyToTarget = FName(TEXT("EnemyToTarget"));
		AI_State = FName(TEXT("AI_State"));
		CharacterType = FName(TEXT("CharacterType"));
		AttackWaitTime = FName(TEXT("AttackWaitTime"));
	}

	FName TargetLocation;
	FName EnemyToTarget;
	FName AI_State;
	FName CharacterType;
	FName AttackWaitTime;
};

UCLASS()
class YARRWARS_API ABaseAIController : public AAIController
{
	GENERATED_BODY()
public:
	/* CONSTRUCTOR */
	ABaseAIController();

	/* METHODS */
	// Gets a pointer to the blackboard component
	FORCEINLINE UBlackboardComponent* GetBlackboard() const { return blackboard; }
	// Returns the owning character of the controller
	FORCEINLINE AAICharacter* GetOwner() const { return owner; }
	// Sets the target on the blackboard
	void SetEnemyTarget(AActor* target) const;
	// Sets the state of the character
	void SetAiState(EAIState& state) const;
	// Sets the type of character that this is
	void SetCharacterType(ECharacterType type) const;
	// Sets the target location
	void SetTargetLocation(FVector location) const;
	// Sets the attack wait time
	void SetAttackWaitTime(float waitTime) const;
	
	/* PROPERTIES */

protected:
	/* METHODS */
	// Called when the pawn is spawned into the game, and used to setup the blackboard & bt
	virtual void OnPossess(APawn* InPawn) override;
	


	/* ---------- */
	/* PROPERTIES */
	/* ---------- */
	// Behaviour tree component reference
	UBehaviorTreeComponent* behaviorTree;
	// Blackboard component reference
	UBlackboardComponent* blackboard;
	// Stores all the blackboard keys for the characters
	const FBlackboardKeys bbKeys = FBlackboardKeys();
	// Stores the owning character of this controller
	AAICharacter* owner;

	
	
	
	
};
