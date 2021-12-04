// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <activation.h>

#include "Character/BaseCharacter.h"


#include "AICharacter.generated.h"

/* FORWARD DECLARATION */
class USkeletalMeshComponent;
class USkeletalMesh;
class UDataTable;
class UBehaviorTree;
class APathPoint;
class AQuartersController;
class ACoin;

UENUM(Blueprintable)
enum EAIState
{
	PATH_POINT,
	ATTACK_TOWER,
	ATTACK_PLAYER,
	ATTACK_CHEST,
	AI_DEAD
};

/**
 * Created By: Keegan Miller
 * Last Edit By: Keegan Miller
 * Edit Date: 30/08/2021
 * Version: 1.1
 * Description: the AI Character Class
 */
UCLASS()
class YARRWARS_API AAICharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	/* CONSTRUCTOR */
	AAICharacter();

	/* METHODS */
	virtual void Tick(float DeltaSeconds) override;

	// Sets up what the AI will be doing (following a path, following a tower etc...)
	void GenerateAIState();

	/* GETTERS & SETTERS */
	
	// Return what type of character this is
	ECharacterType GetCharacterType() const { return characterType; }
	// Setups the character details & calls method to determine what will happen
	virtual void SetupCharacter(const ECharacterType character) override;
	// Changes the state of the AI Character 
	void ChangeState(const EAIState newState);

	/* PROPERTIES */
	
	// References to the behavior tree
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	UBehaviorTree* BehaviorTree;

	// Path point that this character will be following
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	APathPoint* PathPoint;

	virtual void Attack() override;
	// Drops a coin in a space around the character
	void DropCoin();
	
	

protected:
	/* METHODS */
	virtual void BeginPlay() override;

private:
	/* METHODS */
	
	// Find a path point that's in the world
	void FindPathPoint();
	// Find a tower that has been placed in the world
	void FindTower();

	void TriggerGenerateStateTimer();

	/* PROPERTIES */
		
	// Current state of the AI (following a path, attacking etc...)
	EAIState aiState;

	// What the AI is targeting to attack
	AActor* target;

	// Reference to the Captains Quarters
	AQuartersController* captainQuarters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Drops", meta=(AllowPrivateAccess="true"))
	TSubclassOf<class ACoin> coin;

	// Timer to handle generating a state
	FTimerHandle generatePathTimer;

	

	

	
	
};
