// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterAnimInstance.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/BaseCharacter.h"

UCharacterAnimInstance::UCharacterAnimInstance()
{
	movementSpeed = 0;
	
	isGrounded = false;
	owningActor = nullptr;
}

/// <summary>
///	Called when the class is loaded into the game
/// </summary>
void UCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	
	// Get the owning Actor & cast it to the base character class
	owningActor = Cast<ABaseCharacter>(GetOwningActor());
}

/// <summary>
/// Called every frame
/// </summary>
void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	// Make sure we have an owning actor before updating the animation
	if(owningActor != nullptr)
	{
		Super::NativeUpdateAnimation(DeltaSeconds);

		// Set the movement speed of the character
		movementSpeed = GetMovementSpeed();
		// Set if the character is grounded or not
		isGrounded = IsGrounded();
	} else
	{
		
	}
}

/// <summary>
///	Plays a specific animation via the animation name
/// </summary>
void UCharacterAnimInstance::PlayAnimMontage(const FName animationName)
{
	if(animationMontages != nullptr)
	{
		static const FString ContextString(TEXT("Animation Montage Data Table"));
		FCharacterAnimationMontage* montage_data_table = animationMontages->FindRow<FCharacterAnimationMontage>(
			animationName, ContextString, true);

		// if the data table isn't null & the animation montage isn't null than play the animation
		if(montage_data_table != nullptr && montage_data_table->AnimationMontage != nullptr)
		{
			if(GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Player Char Attacking"));
			}

			
			Montage_Play(montage_data_table->AnimationMontage);
		}
	}
}

void UCharacterAnimInstance::PlayAnimMontage(const EAnimationCategory montageCategory)
{
	if(animationMontages != nullptr)
	{
		
		static const FString ContextString(TEXT("Animation Montage Data Table"));

		// Array that stores all the animations. in final will only have the animations that we specified
		TArray<FCharacterAnimationMontage*> animations;
		// Get all the rows of the animation
		animationMontages->GetAllRows(ContextString, animations);

		// Loop through animations
		for(auto& animation : animations)
		{
			// If the animation is the category we want, than remove it from the array
			if(animation->AnimationCategory != montageCategory)
			{
				animations.Remove(animation);
			}
		}

		if(animations.Num() > 0)
		{
			// Get the random number to play the animation
			int random_val = FMath::RandRange(0, (animations.Num() - 1));
			// Make sure that the value is withing the index of the animations
			if(random_val < animations.Num())
			{
				// Assign the animation
				UAnimMontage* montage_to_play = animations[random_val]->AnimationMontage;
				// Ensure the animation isn't null & play the animation
				if(montage_to_play != nullptr)
					Montage_Play(montage_to_play);
			}
		}
		
	}
}

/// <summary>
///	Calculates the movement speed of the character
/// </summary>
/// /// <returns>Movement Speed of the character</returns>
float UCharacterAnimInstance::GetMovementSpeed()
{
	// Ensure we have an owning actor,
	// than get the magnitude of the movement vector &  return it
	if(owningActor != nullptr)
	{
		return owningActor->GetVelocity().Size();
	}

	return 0.0f;
}

/// <summary>
/// Checks if the character is grounded or not
/// </summary>
/// <returns>If the character is grounded or not</returns>
bool UCharacterAnimInstance::IsGrounded()
{
	if(owningActor != nullptr)
	{
		return owningActor->GetMovementComponent()->IsFalling();
	}
	
	return false;
}
