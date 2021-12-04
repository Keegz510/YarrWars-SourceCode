// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "GameLevel.generated.h"



/**
 * Created By: Keegan Miller
 * Last Edit By: Keegan Miller:
 * Date Edited: 19/08/2021
 * Version 1.0
 * Description: This class stores & controls everything in the level
 */

/* FORWARD DECLARATION */
class APathPoint;

UCLASS()
class YARRWARS_API AGameLevel : public ALevelScriptActor
{
	GENERATED_BODY()
public:

	/* METHODS */

	
	// Adds a path point the path point array
	void AddPathPoint(APathPoint* point);
	// Removes a path point from the list
	void RemovePathPoint(APathPoint* point);
	
	// Gets a path point a specific point
	APathPoint* GetPathPoint(int index) const;
	// Gets a random path point from the path point array
	APathPoint* GetRandomPathPoint() const;
	
private:
	/* PROPERTIES */
	// Array to store all the path points
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Path Points", meta=(AllowPrivateAccess="true",
		ToolTip="An Array that store all the path points currently in the level"))
	TArray<APathPoint*> pathPointsInLevel;
	// TODO: Add All Towers here
};
