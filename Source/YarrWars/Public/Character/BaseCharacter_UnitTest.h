// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseUnitTest.h"
#include "BaseCharacter_UnitTest.generated.h"

/* FORWARD DECLARATIONS */
class ABaseCharacter;

/**
 * Created By: Keegan Miller
 * Edited By: Keegan Miller
 * Edit Date: 17/08/2021
 * Version 1.0
 * Description: Unit testing for the characters
 */
UCLASS()
class YARRWARS_API ABaseCharacter_UnitTest : public ABaseUnitTest
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;
	virtual void RunTest() override;
private:
	ABaseCharacter* character;			// Character to test (this wil be the player character


	
};
