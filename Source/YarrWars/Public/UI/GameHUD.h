// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHUD.generated.h"

/**
 * Created By: Keegan Miller
 * Last Edit By: Keegan Miller
 * Date Edited: 30.08.2021
 * Version: 1.0
 * Description: Handles the player UI
 */
 
 /* FORWARD DECLARATION */
class APlayerCharacter;
class UTextBlock;
class UProgressBar;
class UCanvasPanel;
class UGameHUD;
 
UCLASS()
class YARRWARS_API UGameHUD : public UUserWidget
{
	GENERATED_BODY()
public:
    virtual void NativeConstruct() override;

	// Gets the new total
	void UpdateTotal(const int32 total);
	// Sets the characters current health
	void UpdateHealth(const float health);
	// Update the wave information
	void UpdateTotalEnemies(const FText waveInfo);
	
private:
	// Reference to the player character
    APlayerCharacter* playerCharacter;
	// Reference to the player hud
	UGameHUD* hud;



	// Text block to display the coins
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true", BindWidget))
	UTextBlock* coinTotal;

	// Text block to display what wave it is & how many enemies are left
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true", BindWidget))
	UTextBlock* waveAndEnemyCount;

	// Progress bar that displays the players health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true", BindWidget))
	UProgressBar* playerHealthBar;
	

};
