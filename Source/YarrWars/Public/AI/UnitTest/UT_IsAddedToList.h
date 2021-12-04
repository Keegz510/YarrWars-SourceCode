// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseUnitTest.h"
#include "UT_IsAddedToList.generated.h"

/**
 * 
 */
UCLASS()
class YARRWARS_API AUT_IsAddedToList : public ABaseUnitTest
{
	GENERATED_BODY()
public:
	virtual void Tick(float deltaSeconds) override;

	TArray<class AActor*> pathPoints;
private:
	virtual void RunTest() override;
		
	
};
