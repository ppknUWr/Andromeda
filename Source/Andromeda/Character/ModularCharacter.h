// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterStats.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ModularCharacter.generated.h"


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


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USkeletalMeshComponent*> BodyParts;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UCameraComponent* Camera;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FCharacterStats CurrentsStats;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FCharacterStats MaxStats;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FWeaponExpGain WeaponExpGain;

	void SetStat(float FCharacterStats::* StatsField, float Value);
	
	//React to hit, based on hit result 's bone name
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ReactToHit(FName BoneName);

	//Return true if Stamina is above 0
	UFUNCTION(BlueprintCallable)
	bool UseStamina(float StaminaToUse);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWeaponComponent* Weapon;

protected:

	void ApplyRagdoll();
	void LeftMouseClick();
	
	float WalkSpeed = 600;
	float SprintSpeed = 1100;
	

public:
	
	FORCEINLINE void MoveForward(float Value) { AddMovementInput(GetActorForwardVector(), Value); }
	FORCEINLINE void MoveRight(float Value) { AddMovementInput(GetActorRightVector(), Value); }
	FORCEINLINE void SprintStart() { GetCharacterMovement()->MaxWalkSpeed = SprintSpeed; }
	FORCEINLINE void StopSprinting() { GetCharacterMovement()->MaxWalkSpeed = WalkSpeed; }
	FORCEINLINE void BeginCrouch() { Crouch(); }
	FORCEINLINE void EndCrouch() { UnCrouch(); }
};
