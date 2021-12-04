// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MainMenuController.generated.h"

/* FORWARD DECLARATIONS */
class UUserWidget;

/**
 * Created By: Keegan Miller
 * Date: 16/08/2021
 * Description: This class mainly handles the loading of the Main menu
 * Version 1.0
 */
UCLASS()
class YARRWARS_API AMainMenuController : public ALevelScriptActor
{
	GENERATED_BODY()
public:

	/* CONSTRUCTORS */
	AMainMenuController();

	/* METHODS */

	/* PROPERTIES */
private:
	
	/* METHODS */
	virtual void BeginPlay() override;
	void LoadMainMenu();

	/* PROPERTIES */
	
	// Subclass Blueprint of the main menu property
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI Menu", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UUserWidget> subclassMainMenuWidget;
	// Property to store the Main Menu once created
	UUserWidget* mainMenuWidget;
};
