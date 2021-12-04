// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseUnitTest.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void ABaseUnitTest::Tick(float deltaSeconds)
{
	Super::BeginPlay();
	RunTest();
}

void ABaseUnitTest::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseUnitTest::RunTest()
{
	// LEAVE BLANK
}

void ABaseUnitTest::Finished()
{
	if(result)
	{
		FinishTest(EFunctionalTestResult::Succeeded, message);
	} else
	{
		FinishTest(EFunctionalTestResult::Failed, message);
	}

	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
}
