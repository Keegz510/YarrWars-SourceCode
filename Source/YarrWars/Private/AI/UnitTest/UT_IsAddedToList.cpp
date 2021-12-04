// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/UnitTest/UT_IsAddedToList.h"
#include "Character/AICharacter.h"
#include "Character/PathPoint.h"
#include "Kismet/GameplayStatics.h"
#include "Levels/GameLevel.h"

void AUT_IsAddedToList::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
}

void AUT_IsAddedToList::RunTest()
{
	// Get all the actors of path points & cast the first one
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), TSubclassOf<APathPoint>(), pathPoints);
	APathPoint* point = Cast<APathPoint>(pathPoints[0]);

	// make sure we have the point & see if they are the same
	if(point != nullptr)
	{
		APathPoint* levelPoint = Cast<AGameLevel>(GetWorld()->GetLevelScriptActor())->GetPathPoint(0);
		if(levelPoint == point)
		{
			message = "Point has been added to the world";
			result = false;
			Finished();
		} else
		{
			message = "Point was not added to the array";
			result = false;
			Finished();
		}
	} else
	{
		message = "Path point not found in the world";
		result = false;
		Finished();
	}
}
