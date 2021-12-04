// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Button.h"


void UMainMenu::NativeConstruct()
{
	// Add OnClick events to each of the buttons
	playButton->OnClicked.AddDynamic(this, &UMainMenu::LoadNewGame);
	settingsButton->OnClicked.AddDynamic(this, &UMainMenu::OpenSettings);
	exitButton->OnClicked.AddDynamic(this, &UMainMenu::ExitGame);
	
}

/// <summary>
/// Opens the main scene
/// </summary>
void UMainMenu::LoadNewGame()
{
	UGameplayStatics::OpenLevel(this, FName("Game_Scene"));
}

/// <summary>
/// Will open the settings menu & close the main menu
/// </summary>
void UMainMenu::OpenSettings()
{
	if(GEngine != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Not yet implemented"));
	}
}

/// <summary>
///	Handles closing the game to the desktop
/// </summary>
void UMainMenu::ExitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0),
		EQuitPreference::Quit, true);
}
