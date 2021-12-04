// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "BaseUnitTest.generated.h"

/**
 * 
 */
UCLASS()
class YARRWARS_API ABaseUnitTest : public AFunctionalTest
{
	GENERATED_BODY()
public:
	virtual void Tick(float deltaSeconds) override;
	

protected:
	virtual void BeginPlay() override;
	virtual void RunTest();
	void Finished();

	FString message;
	bool result;
	
};
