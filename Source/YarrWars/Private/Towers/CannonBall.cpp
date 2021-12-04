// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers/CannonBall.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Character/AICharacter.h"
#include "Character/BaseCharacter.h"

// Sets default values
ACannonBall::ACannonBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	

	ballCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = ballCollider;

	ballCollider->SetGenerateOverlapEvents(true);
	ballCollider->SetCollisionProfileName("OverlapAll");


	// Create the objects
	ballMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	ballMesh->SetupAttachment(ballCollider);


	movementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	movementComponent->SetUpdatedComponent(ballCollider);
	movementComponent->bRotationFollowsVelocity = true;
	movementComponent->bShouldBounce = true;
	movementComponent->Bounciness = 0.1;
	movementComponent->ProjectileGravityScale = 1.0f;

	// How long the ball last in the world
	InitialLifeSpan = 5.0f;

	// Added Collision on hit
	ballCollider->OnComponentBeginOverlap.AddDynamic(this, &ACannonBall::OnBeginOverlap);

}

// Called when the game starts or when spawned
void ACannonBall::BeginPlay()
{
	Super::BeginPlay();

	// Set the speeds on begin play
	movementComponent->InitialSpeed = InitialSpeed;
	movementComponent->MaxSpeed = maxSpeed;

	

}

void ACannonBall::FireProjectile(const FVector fireDirection)
{
	movementComponent->Velocity = fireDirection * movementComponent->InitialSpeed;
}



void ACannonBall::OnBeginOverlap(UPrimitiveComponent* component, AActor* otherActor, UPrimitiveComponent* otherComp,
	int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("HIT SOMETHING"));
	// Check that we haven't collided with our sevles & the thing we did collide with can take damage
	if (otherActor != this && otherActor->ActorHasTag("TakesDamage"))
	{
		// Cast the hit to base character & Apply Damage
		if (ABaseCharacter* character = Cast<ABaseCharacter>(otherActor))
		{
			character->CharacterTakeDamage(damagePerBall);
		}
	}
}
