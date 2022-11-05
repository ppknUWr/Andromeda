// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Andromeda/Combat/WeaponComponent.h"
#include "Andromeda/Equipment/WeaponItem.h"
#include "CharacterStats.h"
#include "GameFramework/Character.h"
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
	FCharacterStats StatsEXP;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FWeaponExpGain WeaponExpGain;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FWeaponExpGain WeaponExp;

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

public:
	
	FORCEINLINE void MoveForward(float Value) { AddMovementInput(GetActorForwardVector(), Value); }
	FORCEINLINE void MoveRight(float Value) { AddMovementInput(GetActorRightVector(), Value); }
	FORCEINLINE void LeftMouseClick() { Weapon->WeaponItem->LeftMouseClick(GetMesh()); }
};
