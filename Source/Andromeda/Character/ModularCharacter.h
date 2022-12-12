// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterStats.h"
<<<<<<< HEAD
#include "Andromeda/Equipment/WeaponItem.h"
#include "Andromeda/SaveSystem/SaveableInterface.h"
=======
>>>>>>> origin/master
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ModularCharacter.generated.h"

class UItem;
class UInventoryComponent;
class UWeaponComponent;
class UCoins;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonClicked, EInputEvent, InputEvent);

UCLASS(Abstract)
class ANDROMEDA_API AModularCharacter : public ACharacter, public ISaveableInterface
{

	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AModularCharacter();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;


public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USkeletalMeshComponent*> BodyParts;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USpringArmComponent* SpringArm;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, SaveGame)
	FCharacterStats CurrentsStats;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, SaveGame)
	FCharacterStats MaxStats;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, SaveGame)
	FCharacterStats StatsEXP;
	
	void SetCurrentStat(float FCharacterStats::* StatsField, float Value);
	void SetMaxStat(float FCharacterStats::* StatsField, float Value);
	void SetStatExp(float FCharacterStats::* StatsField, float Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, SaveGame)
	TMap<FName, float> WeaponsStats;

	UFUNCTION(BlueprintCallable)
	void SetWeaponStat(FName StatName, float Value);

	UFUNCTION(BlueprintPure)
	float GetWeaponStat(FName StatName);

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAcess = "true"))
	UInventoryComponent* Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coins", meta = (AllowPrivateAcess = "true"))
	UCoins* Coins;

	void SetStat(float FCharacterStats::* StatsField, float Value);

	//React to hit, based on hit result 's bone name
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ReactToHit(FName BoneName);

	//Return true if Stamina is above 0
	UFUNCTION(BlueprintCallable)
	bool UseStamina(float StaminaToUse);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWeaponComponent* Weapon;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	ECharacterState CharacterState = ECharacterState::IDLE;

	UPROPERTY(BlueprintAssignable)
	FOnButtonClicked OnLeftMouseButtonClicked;

	UPROPERTY(BlueprintAssignable)
	FOnButtonClicked OnRightMouseButtonClicked;
	
	UFUNCTION(BlueprintCallable, Category = "Items")
	void UseItem(UItem* Item);

	int32 ComboCounter = 0;
protected:

	void ApplyRagdoll();

	void InteractWithActor(AActor* InteractableActor);
	AActor* CastLineTrace();

	UPROPERTY(BlueprintReadWrite)
	AActor* LastSeenInteractableObject = nullptr;
	
	void LeftMouseClick();
	void LeftMouseRelease();
	
	float WalkSpeed = 600;
	float SprintSpeed = 1100;

	void ZoomIn();
	void ZoomOut();

	virtual void OnActorLoaded() override;
	
public:
	
	FORCEINLINE void MoveForward(float Value) { AddMovementInput(GetActorForwardVector(), Value); }
	FORCEINLINE void MoveRight(float Value) { AddMovementInput(GetActorRightVector(), Value); }
	FORCEINLINE void SprintStart() { GetCharacterMovement()->MaxWalkSpeed = SprintSpeed; }
	FORCEINLINE void StopSprinting() { GetCharacterMovement()->MaxWalkSpeed = WalkSpeed; }
	FORCEINLINE void BeginCrouch() { Crouch(); }
	FORCEINLINE void EndCrouch() { UnCrouch(); }
	FORCEINLINE void Interact() { InteractWithActor(CastLineTrace()); };
};
