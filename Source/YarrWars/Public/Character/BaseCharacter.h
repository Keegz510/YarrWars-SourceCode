// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/DataTable.h"


#include "BaseCharacter.generated.h"

/* FORWARD DECLARATIONS */
class UAnimInstance;
class USkeletalMesh;
class UDataTable;
class UCharacterAnimInstance;
class UStaticMesh;
class UStaticMeshComponent;
class UBoxComponent;
class UAudioComponent;
class USoundBase;
class AWaveController;

UENUM()
enum ECharacterState
{
	IDLE,
	WALKING,
	DEAD
};

UENUM(BlueprintType)
enum ECharacterType
{
	MALE_PLAYER,
	FEMALE_PLAYER,
	SKELETON,
};

UENUM(BlueprintType)
enum EAudioCategory
{
	Combat,
	Dying,
	Footstep,
	Damage,
	Spawn,
	Misc
};

USTRUCT(BlueprintType)
struct FCharacterAccessiories
{
	GENERATED_BODY();
public:
	// Mesh of the accessory we want to attach
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* AccMesh;
	// Name of the socket to attach to 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SocketName;
	// Location to use when attaching
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector location;
	// Rotation of the mesh when attaching
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator rotation;
};

USTRUCT(BlueprintType)
struct FCharacterDataTable : public FTableRowBase
{
	GENERATED_BODY()
public:
	/* CONSTRUCTORS */
	FCharacterDataTable() {}
	~FCharacterDataTable() {}

#pragma region Character Details

	/* Name of the character (e.g: Skeleton, John, Henry */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Details")
	FString CharacterName;
	/* Description about what the character can & can't do */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Details")
	FString CharacterDescription;
	/* What type of character class is this */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Details")
	TEnumAsByte<ECharacterType> CharacterType = ECharacterType::SKELETON;

#pragma endregion



#pragma region Skills

	/* Max amount of health this character has */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Skills")
	float MaxHealth;
	/* How much damage this character will deal */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Skills")
	float AttackPoints;

#pragma endregion

#pragma region Misc

	// How many coins this character has/gives
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	int32 CharacterCoins;
	/* Animation blueprint that the character uses */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Animation")
	TSubclassOf<UCharacterAnimInstance> AnimBlueprint;		// TODO: Check that this is the correct class to store

#pragma endregion
	

#pragma region Character Meshes


	/* The mesh that will be displayed when the character is loaded */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	USkeletalMesh* CharacterMesh = nullptr;
	// Weapon that the character will hold
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMesh* WeaponMesh;
	// List of accessories the character can wear
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	TArray<FCharacterAccessiories> accessories;
	
#pragma endregion

	#pragma region Data Tables

	// The animation montage for this character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Tables")
	UDataTable* AnimationDataTable;

	// Audio For the character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Tables")
	UDataTable* AudioDataTable;

	#pragma endregion

	

	
};

USTRUCT(BlueprintType)
struct FCharacterAudio : public FTableRowBase
{
	GENERATED_BODY()
public:
	// Sound file that will be played
	UPROPERTY(EditAnywhere)
	USoundBase* SoundFile;
	// Category of the sound
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EAudioCategory> AudioCategory;
};

/**
 * Created By: Keegan Miller
 * Last Edit By: Keegan Miller
 * Last Edit Date: 28/08/2021
 * Version: 1.4
 * Description: This class is used to setup all the characters. This is considered a base class
 */
UCLASS()
class YARRWARS_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	/* CONSTRUCTORS */
	// Sets default values for this character's properties
	ABaseCharacter();

	/* METHODS */
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void CharacterTakeDamage(float damagePoints);

	virtual void SetupCharacter(const ECharacterType character);
	// Plays the attack animation and enables colliders on the weapons
	virtual void Attack();
	// Plays a specific sound on the audio component
	void PlayAudio(USoundBase* audio) const;
	// Will select a random foot step to play
	USoundBase* GetRandomAudio(EAudioCategory category);
	

	/* PROPERTIES */

	/* GETTERS & SETTERS */
	// Get the characters current health
	FORCEINLINE float GetCurrentHealth() const { return currentHealth; }
	// Get the characters Max Health
	FORCEINLINE float GetMaxHealth() const { return maxHealth; }
	// Get the characters Animation Instance
	FORCEINLINE UAnimInstance* GetAnimInstance() const { return characterAnim; }
	// Get the current state of the character
	FORCEINLINE ECharacterState GetCurrentState() const { return characterState; }
	void SetCharacterState(ECharacterState state);
	// Enables the collider and starts timer for attacking
	virtual void StartAttack();
	// Finishes the attack
	virtual void FinishAttack();

	int32 characterCoins;		// How many coins the character has
	

	/* GETTERS */
	FName GetCharacterName() const { return characterName; }
	
protected:
	/* METHODS */
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Get the type of character this is as a string
	FName GetCharacterTypeAsString();

	// Loads all the animaton data
	void LoadAnimations(FCharacterDataTable& dataTable);
	// Loads all the weapon data
	void LoadWeaponMesh(FCharacterDataTable& dataTable);
	// Handles loading of the audio data
	void LoadAudioData(FCharacterDataTable& dataTable);
	// Handles loading of the accessories
	void LoadAccessories(FCharacterDataTable& dataTable);
	// Overlap method for when the weapon collision hits something
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* component, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
	
	// Handles destroying the character
	void RemoveCharacter();
	
	

	

	/* PROPERTIES */
	// The max health that this character has
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health", meta=(AllowPrivateAccess="true"))
	float maxHealth = 100.0f;
	float currentHealth;

	ECharacterState characterState;		// Current state of the character
	UAnimInstance* characterAnim;		// Character animation instance

	// The total amout of damage this character can use on 1 attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attack Settings", meta=(AllowPrivateAccess="true"))
	float attackPoints;

	
	// The name of the character
	FName characterName;
	
	// The skeletal mesh from this character
	USkeletalMeshComponent* characterMesh;

	// Mesh that for the weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* weaponMesh;

	// Collider for the weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(AllowPrivateAccess="true"))
	UBoxComponent* weaponCollider;

	/* Data table that we use to load the character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data Tables", meta=(AllowPrivateAccess="true"))
	UDataTable* characterDataTable;

	// Check this to load the data on being play, otherwise we will wait to setup the character
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Mesh Loading", meta=(AllowPrivateAccess="true"))
	bool loadOnPlay;

	// The type of character that will load when we setup the character
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh Loading\|Character Details", meta=(AllowPrivateAccess="true", EditCondition="loadOnPlay"))
    TEnumAsByte<ECharacterType> characterType;

	// If the character is attacking or not
	bool isAttacking = false;

	// Audio Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Audio", meta=(AllowPrivateAccess="true"))
	UAudioComponent* audioComponent;

	// Array of the footstep audio
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Audio", meta=(AllowPrivateAccess="true"))
	TArray<USoundBase*> footstepAudioTracks;

	// Array of audio sounds the character can perform
	TArray<FCharacterAudio*> audioData;

	// reference to the wave controller
	AWaveController* waveController;

	// Timer to handles removing of dead character
	FTimerHandle destroyTimer;
	
	// How long dead enemies stay in the scene
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Destroy Settings", meta=(AllowPrivateAccess="true"))
	float destroyWaitTime = 3.0f;
	
};
	
