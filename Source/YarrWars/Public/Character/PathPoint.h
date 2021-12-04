// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PathPoint.generated.h"
/**
* Created By: Keegan Miller
* Last Edit By: Keegan Miller
* Last Edit Date: 19/08/2021
* Version: 1.0
* Description: This class stores the data for a path point that the AI Character will follow
*/

/* FORWARD DECLARATIONS */
class AAICharacter;


UCLASS()
class YARRWARS_API APathPoint : public AActor
{
	GENERATED_BODY()
	
public:
	/* CONSTRUCTORS */
	// Sets default values for this actor's properties
	APathPoint();

	/* METHODS */
	// Assigns a character to the path 
	void AssignCharacter(AAICharacter* assigningCharacter);
	// Sets the next point on the path
	void IncrementPath();

	

	/* GETTERS */
	// Returns the next point
	FVector GetPointLocation();			// TODO: Replace this with a method that gets the current point as there is no point getting the next one
	// Returns if the point is assigned or not
	bool IsPointFree() const { return character == nullptr; }
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	/* METHODS */
	// Adds the point the Level array that stores all the points
	void CreatePoint();
	
	/* PROPERTIES */
	// Stores each point of the path
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true", ToolTip="Each point of the path", MakeEditWidget))
	TArray<FVector> pathPoints;
	// What path we are currently at with this index
	int32 currentPathIndex = 0;

	// Character that is following this path
	AAICharacter* character;

	void PointReached();
	

};
