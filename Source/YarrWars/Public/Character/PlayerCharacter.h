// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

/* FORWARD DECLARATIONS */
class UCameraComponent;
class USpringArmComponent;
class UGameHUD;
class UUserWidget;
class ABuildingSystem;

/**
 * Created By: Keegan Miller
 * Last Edit By: Keegan Miller
 * Date: 04/09/2021
 * Version 1.3
 * Description: This class handles all the actions that the player can do.
 */
UCLASS()
class YARRWARS_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	/* CONSTRUCTORS */
	APlayerCharacter();

	/* METHODS */
	virtual void Tick(float DeltaSeconds) override;
	/* PROPERTIES */
	void AddCoin(const int coin);

	virtual void Attack() override;
	virtual void FinishAttack() override;

	// Returns the player hud UI element
	FORCEINLINE UGameHUD* GetHUD() const { return gameHUD; }
    
protected:
	/* METHODS */
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;

	

private:
	/* METHODS */
	// Handles settings up the spring arm
	UFUNCTION()
	void SetupSpringArm();
	
	// Handles setting up the camera
	UFUNCTION()
	void SetupCamera();

	// Allows the character to move backwards & forwards
	void MoveForward(const float value);
	// Allows the character to move left & right
	void MoveRight(const float value);
	// Setup the widget
	void SetupHUD();
	// Finds all the building areas
	void FindBuildingAreas();

	// Sets the current placing object as the cannon tower
	void SetCannonTower();
	// Sets the current placing object as the flame tower
	void SetFlameTower();
	// Removes any placing objects & toggles the sword
	void ToggleSword();
	// Places the tower in the scene
	void PlaceTower();
	// Handles rotating the tower
	void RotateTower(const float value);


	// Allows for us to rotate on the spot
	void AllowRotation(const bool allow); 


	
	/* PROPERTIES */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Settings", meta=(AllowPrivateAccess="true"))
	USpringArmComponent* cameraBoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Settings", meta=(AllowPrivateAccess="true"))
	UCameraComponent* camera;
	// How far the camera will be from the character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Settings", meta=(AllowPrivateAccess="true"))
	float targetArmLength = 300.0f;

	// Spring arm attach towers to
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Building System", meta=(AllowPrivateAccess="true"))
	USkeletalMeshComponent* placingTowerMesh;
	// How fast the tower rotates around when placing
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Building System", meta=(AllowPrivateAccess="true"))
	float rotationSpeed;
	// The current rotation of the tower
	FRotator towerRotation;

	// Sub class of the hud to create
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HUD", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UUserWidget> playerHUD_Widget;

	// Stores the created user widget
	UUserWidget* playerHUD;
	// Creates reference to the HUD as the game hud
	UGameHUD* gameHUD;

	// Reference to everywhere we can build
	TArray<ABuildingSystem*> buildingAreas;

	// Reference to if the player can attack or not
	bool canAttack = true;

};
