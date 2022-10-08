// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ModularCharacter.generated.h"

UENUM(BlueprintType)
enum class EBodyPart : uint8
{
	HEAD UMETA(DisplayName = "Head"),
	TORSO UMETA(DisplayName = "Torso"),
	ARMS UMETA(DisplayName = "Arms"),
	LEGS UMETA(DisplayName = "Legs"),
	FEET UMETA(DisplayName = "Feet"),
	COUNT UMETA(Hidden)
//
	
};

inline int GetBodyPartIndex(EBodyPart BodyPart)
{
	return static_cast<int>(BodyPart);
}


UCLASS(Abstract)
class ANDROMEDA_API AModularCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AModularCharacter();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USkeletalMeshComponent*> BodyParts;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UCameraComponent* Camera;

public:
	//React to hit, based on hit result 's bone name
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ReactToHit(FName BoneName);

	//Return true if Stamina is above 0
	UFUNCTION(BlueprintCallable)
	bool UseStamina(float StaminaToUse);

protected:
	//Automatically set Health to be clamped between 0 and 100
	void SetHealth(float NewHealth);

	void ApplyRagdoll();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float MaxHealth = 100;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Basic Stats")
	float Health;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float Strength = 20;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float Stamina = 100;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float Dexterity = 20;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool bIsAttacking = false;
};