// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter_UnitTest.h"
#include "Character/BaseCharacter.h"
#include "Kismet//GameplayStatics.h"


void ABaseCharacter_UnitTest::BeginPlay()
{
	Super::BeginPlay();

	// Get the character when we load the game
	character = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void ABaseCharacter_UnitTest::RunTest()
{
	// make sure the character is valid
	if(character != nullptr)
	{
		character->CharacterTakeDamage(10);			// Apply the damage

		// Determine if the test was successful or not
		if(character->GetCurrentHealth() == 90)
		{
			result = true;
			message = "Characters health was reduced by 10";
			Finished();
		} else
		{
			message = "Character has not taken damage - Health:"  + FString::SanitizeFloat(character->GetCurrentHealth());
			result = false;
			Finished();
		}
	} else
	{
		message = "Character not initialized";
		result = false;
		Finished();
	}
}


void ABaseCharacter_UnitTest::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}




