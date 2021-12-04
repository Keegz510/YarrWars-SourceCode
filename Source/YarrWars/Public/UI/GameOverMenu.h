// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverMenu.generated.h"

/**
 * Last Edit By: Keegan Miller
 * Edit Date: 28/08/2021
 * Version 1.0
 * Description: Handles the game over screen
 */

/* FORWARD DECLARATIONS */
class UButton;

UCLASS()
class YARRWARS_API UGameOverMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
private:
	/* METHODS */
	UFUNCTION()
	void Replay();
	UFUNCTION()
	void MainMenu();

	/* PROPERTIES */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget, AllowPrivateAccess="true"))
	UButton* replayBtn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget, AllowPrivateAccess="true"))
	UButton* mainMenuBtn;
	
};
