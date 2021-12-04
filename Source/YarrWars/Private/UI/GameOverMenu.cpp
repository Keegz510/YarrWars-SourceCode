// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameOverMenu.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UGameOverMenu::NativeConstruct()
{
	Super::NativeConstruct();
	replayBtn->OnClicked.AddDynamic(this, &UGameOverMenu::Replay);
	mainMenuBtn->OnClicked.AddDynamic(this, &UGameOverMenu::MainMenu);
}

void UGameOverMenu::Replay()
{
	UGameplayStatics::OpenLevel(this, FName(TEXT("Game_Scene")));
	UE_LOG(LogTemp, Warning, TEXT("Button Clicked"));
}

void UGameOverMenu::MainMenu()
{
	UGameplayStatics::OpenLevel(this, FName("MainMenu"));
}
