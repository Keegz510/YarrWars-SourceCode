// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FollowPathPoint.generated.h"

/**
 * Created By: Keegan Miller
 * Last Edit By: Keegan Miller
 * Edit Date: 22/08/2021
 * Version: 1.0
 * Description: This class is a task for the AI to follow a path point
 */
UCLASS()
class YARRWARS_API UFollowPathPoint : public UBTTaskNode
{
	GENERATED_BODY()
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
