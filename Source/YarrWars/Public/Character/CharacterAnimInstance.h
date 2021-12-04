// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Engine/DataTable.h"
#include "Character/BaseCharacter.h"

#include "CharacterAnimInstance.generated.h"



/**
 * Created By: Keegan Miller
 * Last Edit By: Keegan Miller
 * Date: 25/08/2021
 * Version: 1.2
 * Description: Controller for the Animation instance used by the characters
 */

/* FORWARD DECLARATIONS */
class ABaseCharacter;
class UAnimMontage;

UENUM(BlueprintType)
enum EAnimationCategory
{
	Attack,
	Death
};

/* STRUCTS */
USTRUCT(BlueprintType)
struct FCharacterAnimationMontage : public FTableRowBase
{
	GENERATED_BODY()
public:
	// Animation Montage to play
	UPROPERTY(EditAnywhere)
	UAnimMontage* AnimationMontage;
	// How long the montage plays for
	UPROPERTY(EditAnywhere)
	float MontagePlayTime;
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EAnimationCategory> AnimationCategory;
	
};

UCLASS()
class YARRWARS_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	/* CONSTRUCTORS */
	UCharacterAnimInstance();

	/* METHODS */
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// Plays the specific animation montage
	void PlayAnimMontage(const FName animationName);
	// Plays a random animation of the category
	void PlayAnimMontage(const EAnimationCategory montageCategory);
	

	/* GETTERS */
	// Get the movement speed of this animation instance
	float GetMovementSpeed();
	// Check if the character is on the ground
	bool IsGrounded();
	// Gets the animation data table
	FORCEINLINE UDataTable* GetAnimationMontageTable() const { return animationMontages; }
	// Gets the current state of the character
	FORCEINLINE ECharacterState GetCharacterState() const { return characterState; }
	

	/* SETTERS */
	// Sets the new owner of the anim instance
	FORCEINLINE void SetOwner(ABaseCharacter* newOwner) { owningActor = newOwner; }
	// Sets the data table for the character instance, where we can call animation montages from
	FORCEINLINE void SetMontageDataTable(UDataTable* table) { animationMontages = table; }
	// Sets the new state of the character
	FORCEINLINE void SetCharacterState(ECharacterState newState) { characterState = newState; }
	
	
protected:
	/* PROPERTIES */
		
	// movement speed of the mesh
	UPROPERTY(BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
	float movementSpeed;
	// If the mesh is on the ground 
	UPROPERTY(BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
	bool isGrounded;

	// owning Character of this anim instance
	ABaseCharacter* owningActor;
	// Holds the animation montages for the character
	UDataTable* animationMontages;
	// Character State
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="States")
	TEnumAsByte<ECharacterState> characterState;

	
};
