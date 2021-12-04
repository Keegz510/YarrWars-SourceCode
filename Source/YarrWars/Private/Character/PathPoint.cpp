// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PathPoint.h"
#include "Levels/GameLevel.h"
#include "Kismet/GameplayStatics.h"
#include "Character/AICharacter.h"

// Sets default values
APathPoint::APathPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APathPoint::BeginPlay()
{
	Super::BeginPlay();
	CreatePoint();		// Adds to the path point array
}

/// <summary>
/// Adds this point the path array, called on begin play
///</summary>
void APathPoint::CreatePoint()
{
	// Gets the current level & adds this path point to the path array
	if(auto* level = Cast<AGameLevel>(GetWorld()->GetLevelScriptActor()))
	{
		level->AddPathPoint(this);
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("Adding Point"));
	} else	// DEBUG CODE
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("Cannot get blueprint actor"));
	}
}

/// <summary>
/// When the point has been reached, that change the state & destroy this
/// </summary>
void APathPoint::PointReached()
{
	// Make sure the point is valid than change the state & destroy this
	if(character != nullptr)
	{
		character->ChangeState(EAIState::ATTACK_CHEST);
		//	Destroy(this);			// this may be remove so that we can reuse this
	}
}

/// <summary>
///	Set the character that owns this path point
/// </summary>
void APathPoint::AssignCharacter(AAICharacter* assigningCharacter)
{
	// Make sure that the character is valid & assign it
	if(assigningCharacter != nullptr)
	{
		character = assigningCharacter;
	}
}

/// <summary>
///	Change the current path point to the next one
/// </summary>
void APathPoint::IncrementPath()
{
	// Make sure we have the character assigned
	if(character != nullptr)
	{
		currentPathIndex += 1;		// Increment the path

		// If the path is now larger or equal to the amount of path points than we reset the index.
		if(currentPathIndex >= pathPoints.Num())
		{
			PointReached();				// will switch the AI State
		}
	}
}

/// <summary>
///	Get the next path point location
/// </summary>
FVector APathPoint::GetPointLocation()
{
	return pathPoints[currentPathIndex];			// Get the next path point location
}

