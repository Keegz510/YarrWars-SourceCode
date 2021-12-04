// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UnitTests/UT_SetupCharacter.h"
#include "Character/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"

void AUT_SetupCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AUT_SetupCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AUT_SetupCharacter::RunTest()
{
	character = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if(character != nullptr)
	{
		character->SetupCharacter(ECharacterType::SKELETON);
		GetWorld()->GetTimerManager().SetTimer(timer, this, &AUT_SetupCharacter::WaitBeforeTesting, 2.0f, false);
	} else
	{
		FinishTest(EFunctionalTestResult::Failed, "Character was not initalized");
		Finished();
	}
}

void AUT_SetupCharacter::WaitBeforeTesting()
{
	if(character->GetCharacterName() == "Skeleton")
	{
		FinishTest(EFunctionalTestResult::Succeeded, "Characters Has been created correctly");
		Finished();
	} else
	{
		FinishTest(EFunctionalTestResult::Failed, "Characters name not setup correctly");
		Finished();
	}
}
