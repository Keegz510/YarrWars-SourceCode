// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameHUD.h"

#include <string>

#include "Character/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"

void UGameHUD::NativeConstruct()
{
	Super::NativeConstruct();
	
}

/// <summary>
///	Displays the coin value as text
/// </summary>
/// <param name="total">How many coins the player has</param>
void UGameHUD::UpdateTotal(const int32 total)
{

	// Convert the total passed in to string
	FString total_as_string = FString::FromInt(total);
	// Convert the FString to a FText
	FText total_as_text = FText::AsCultureInvariant(total_as_string);
	// Update text
	coinTotal->SetText(total_as_text);

}

/// <summary>
///	Updates the player health bar with the current health percentage
/// </summary>
/// <param name="health">Total health the player has</param>
void UGameHUD::UpdateHealth(const float health)
{
	auto percentage = health / 100;				// Get the value between 0 & 1
	playerHealthBar->SetPercent(percentage);			// Set the value

}

void UGameHUD::UpdateTotalEnemies(const FText waveInfo)
{
	waveAndEnemyCount->SetText(waveInfo);
}
