// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseUnitTest.h"
#include "UT_SetupCharacter.generated.h"

/**
 * 
 */
UCLASS()
class YARRWARS_API AUT_SetupCharacter : public ABaseUnitTest
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaSeconds) override;

	

protected:
	virtual void BeginPlay() override;
	virtual void RunTest() override;
	void WaitBeforeTesting();

	FTimerHandle timer;
	class ABaseCharacter* character;
};
