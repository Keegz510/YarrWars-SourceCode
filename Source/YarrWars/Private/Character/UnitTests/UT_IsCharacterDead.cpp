// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UnitTests/UT_IsCharacterDead.h"
#include "Character/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"


void AUT_IsCharacterDead::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AUT_IsCharacterDead::BeginPlay()
{
	Super::BeginPlay();
	// Get the player character
	Character = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void AUT_IsCharacterDead::RunTest()
{
	Super::RunTest();
	if(Character != nullptr)
	{
		Character->CharacterTakeDamage(200);
		if(Character->GetCurrentState() == ECharacterState::DEAD)
		{
			message = "Character is dead - Test Passed";
			result = true;
			Finished();
		} else
		{
			result = false;
			message = "Character still alive state: ";
			Finished();
		}
	} else
	{
		result = false;
		message = "Character not initialized";
		Finished();
	}
}
