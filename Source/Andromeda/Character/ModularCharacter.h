// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Andromeda/Interfaces/Interactable.h"
#include "CharacterStats.h"
#include "Andromeda/Equipment/WeaponItem.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ModularCharacter.generated.h"

class UItem;
class UInventoryComponent;
class UWeaponComponent;


UCLASS(Abstract)
class ANDROMEDA_API AModularCharacter : public ACharacter
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
	FCharacterStats CurrentsStats;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FCharacterStats MaxStats;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FCharacterStats StatsEXP;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FWeaponExpGain WeaponExpGain;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FWeaponExpGain WeaponExp;

	void SetCurrentStat(float FCharacterStats::* StatsField, float Value);
	void SetMaxStat(float FCharacterStats::* StatsField, float Value);
	void SetStatExp(float FCharacterStats::* StatsField, float Value);
	void SetWeaponExp(float FWeaponExpGain::* StatsField, float Value);
	void SetWeaponExpGained(float FWeaponExpGain::* StatsField, float Value);
	void AddWeaponExp();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAcess = "true"))
	UInventoryComponent* Inventory;

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

	UFUNCTION(BlueprintCallable, Category = "Items")
	void UseItem(UItem* Item);


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
	


public:
	
	FORCEINLINE void MoveForward(float Value) { AddMovementInput(GetActorForwardVector(), Value); }
	FORCEINLINE void MoveRight(float Value) { AddMovementInput(GetActorRightVector(), Value); }
	FORCEINLINE void SprintStart() { GetCharacterMovement()->MaxWalkSpeed = SprintSpeed; }
	FORCEINLINE void StopSprinting() { GetCharacterMovement()->MaxWalkSpeed = WalkSpeed; }
	FORCEINLINE void BeginCrouch() { Crouch(); }
	FORCEINLINE void EndCrouch() { UnCrouch(); }
	FORCEINLINE void Interact() { InteractWithActor(CastLineTrace()); };
};
