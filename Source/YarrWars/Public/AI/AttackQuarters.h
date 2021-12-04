// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AttackQuarters.generated.h"

/**
 * Created By: Keegan Miller
 * Last Edit By: Keegan Miller
 * Edit Date: 25/08/2021
 * Description: This is an AI for the ai to attack the quarters and drain money from it when they're attacking it
 */
UCLASS()
class YARRWARS_API UAttackQuarters : public UBTTaskNode
{
	GENERATED_BODY()
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;  
};
