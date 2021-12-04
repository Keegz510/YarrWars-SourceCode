// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "MainMenu.generated.h"

/* FORWARD DECLARATIONS */
class UButton;
class UText;

/**
* Created By: Keegan Miller
* Date: 15/08/2021
* Description: This class will control the main menu
* Version 1.1
*/
UCLASS()
class YARRWARS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	/* CONSTRUCTORS */
	virtual void NativeConstruct() override;

	/* METHODS */
	
	
private:
	/* METHODS */
	// Loads the game scene
	UFUNCTION()
	void LoadNewGame();
	// Opens the settings menu & closes this menu
	UFUNCTION()
	void OpenSettings();
	// Exits the game to the desktop
	UFUNCTION()
	void ExitGame();

	/* PROPERTIES */

	// Holds the background for the main menu
	UPROPERTY(meta=(BindWidget))
	UImage* gameBackground;

	// Buttons for the main menu
	UPROPERTY(meta=(BindWidget))
	UButton* playButton;			// On click will load a new game
	UPROPERTY(meta=(BindWidget))
	UButton* settingsButton;		// On click will open the menu button
	UPROPERTY(meta=(BindWidget))
	UButton* exitButton;			// On click will exit the game

	
	

	
	
};
