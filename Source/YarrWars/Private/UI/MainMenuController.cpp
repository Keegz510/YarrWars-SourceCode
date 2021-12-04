// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/UserWidget.h"


AMainMenuController::AMainMenuController()
{
}

void AMainMenuController::BeginPlay()
{
	Super::BeginPlay();
	LoadMainMenu();

	// Enable the mouse when menu loads
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bEnableClickEvents = true;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bEnableMouseOverEvents = true;
}

///<summary>
/// Handles loading & adding the MainMenu to the screen
///</summary>
void AMainMenuController::LoadMainMenu()
{
	// Ensure we have assigned the blueprint, if we haven't display and error or quit the game
	if(subclassMainMenuWidget != nullptr)
	{
		// Create the user widget and store it in the below property
		mainMenuWidget = CreateWidget<UUserWidget>(GetWorld(), subclassMainMenuWidget);

		// Ensure that we have created the widget correctly and add it to the viewport
		if(mainMenuWidget != nullptr)
		{
			mainMenuWidget->AddToViewport();
		} else
		{
			// Print debug message on screen if we are in the editor otherwise Exit Game
			if(GEngine != nullptr)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, TEXT("Error Loading Main Menu"));
			} else
			{
				UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
			}
		}
			
		
	} else
	{
		// Print debug message on screen if we are in the editor otherwise Exit Game
		if(GEngine != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, TEXT("Error Loading Main Menu"));
		} else
		{
			UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
		}
	}
}
