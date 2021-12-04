// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "IncrementPathIndex.generated.h"

/**
 * Created By: Keegan Miller
 * Last Edit By: Keegan Miller
 * Date Edit: 22/08/2021
 * Version: 1.0
 * Description: Increments the path index when it's reached
 */
UCLASS()
class YARRWARS_API UIncrementPathIndex : public UBTTaskNode
{
	GENERATED_BODY()
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
