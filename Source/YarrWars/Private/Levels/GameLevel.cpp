// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/GameLevel.h"
#include "Character/PathPoint.h"

/// <summary>
///	Adds a path point the path point array
/// </summary>
void AGameLevel::AddPathPoint(APathPoint* point)
{
	// Make sure that the path point is valid & add it to the array
	if(point != nullptr && !pathPointsInLevel.Contains(point))
	{
		pathPointsInLevel.Add(point);
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("Point has been added"));
		for(auto p : pathPointsInLevel)
		{
			UE_LOG(LogTemp, Warning, TEXT("Point"));
		}
	}
}

/// <summary>
///	Removes a point from the array (this is mainly done once the character has completed their path)
///	(we also may never us this as it will be a reusable point)
/// </summary>
void AGameLevel::RemovePathPoint(APathPoint* point)
{
	// Ensure that the point is not null, the point is in the list & than remove it from the array
	if(point != nullptr && pathPointsInLevel.Contains(point))
	{
		pathPointsInLevel.Remove(point);
	}
}

/// <summary>
///	Gets the specific path point from the points array
/// </summary>
/// <param name="index">Path point we want to get</param>
APathPoint* AGameLevel::GetPathPoint(int index) const
{
	// Ensure that the index we are reaching is within the bounds of the array & return it
	if(index < pathPointsInLevel.Num())
	{
		// Make sure that the point is free before returning it
		if(pathPointsInLevel[index]->IsPointFree())
		{
			return pathPointsInLevel[index];
		}
	}

	return nullptr;			// If the point is in use than return this & the character class will change the state
}

/// <summary>
///	Gets a random path point for the path array
/// </summary>
APathPoint* AGameLevel::GetRandomPathPoint() const
{
	// Loop through the amount of points in the array
	for(int i = 0; i < pathPointsInLevel.Num(); ++i)
	{
		// Generate a random value from the size of the array
		const auto randVal = FMath::RandRange(0, pathPointsInLevel.Num());
		// Get the random point for the array 
		APathPoint* point = pathPointsInLevel[randVal];
		
		// Is the point is free than return that point
		if(point->IsPointFree()) return point;
	}

	return nullptr;		// If we don't find a free point we will change the state of the character in the setup class
}
