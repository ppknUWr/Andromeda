// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterStats.h"
#include "Andromeda/SaveSystem/SaveableInterface.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ModularCharacter.generated.h"

class UItem;
class UActionComponent;
class UInventoryComponent;
class UWeaponComponent;
class UCoins;
class AThrowableActor;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UActionComponent* ActionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Components")
	UWeaponComponent* LeftHandWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Components")
	UWeaponComponent* RightHandWeapon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ModularCharacter|Mesh")
	TMap<EBodyPart, TObjectPtr<USkeletalMesh>> CharacterMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ModularCharacter|Mesh")
	TObjectPtr<USkeleton> CharacterSkeleton;
	
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
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	ECharacterState CharacterState = ECharacterState::IDLE;

	UPROPERTY(BlueprintAssignable)
	FOnButtonClicked OnLeftMouseButtonClicked;

	UPROPERTY(BlueprintAssignable)
	FOnButtonClicked OnRightMouseButtonClicked;
	
	UFUNCTION(BlueprintCallable, Category = "Items")
	void UseItem(UItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Items")
	void BuyItem(UItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Items")
	void SellItem(UItem* Item);

	// Most of the time it's empty, unsless player starts an interaction with trader.
	//  Didn't had any better ideas to connect the selling of an item.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UInventoryComponent* TraderInventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCoins* TraderCoins;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool PlayerTrading;

	UPROPERTY(BlueprintReadWrite)
	int32 ComboCounter = 0;
	
	void MouseButtonPressed(FKey Key);
	void MouseButtonReleased(FKey Key);
	
	UPROPERTY(BlueprintReadWrite)
	AThrowableActor* SpawnThrowableActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* InteractionWidgetRef;
protected:

	void ApplyRagdoll();

	void InteractWithActor(AActor* InteractableActor);
	AActor* CastLineTrace();

	UPROPERTY(BlueprintReadWrite)
	AActor* LastSeenInteractableObject = nullptr;
	

	
	float WalkSpeed = 600;
	float SprintSpeed = 1100;

	void ZoomIn();
	void ZoomOut();

	virtual void OnActorLoaded() override;

	UFUNCTION(BlueprintCallable)
	void MergeMeshes();
	
public:
	
	FORCEINLINE void MoveForward(float Value) { AddMovementInput(GetActorForwardVector(), Value); }
	FORCEINLINE void MoveRight(float Value) { AddMovementInput(GetActorRightVector(), Value); }
	FORCEINLINE void SprintStart() { GetCharacterMovement()->MaxWalkSpeed = SprintSpeed; }
	FORCEINLINE void StopSprinting() { GetCharacterMovement()->MaxWalkSpeed = WalkSpeed; }
	FORCEINLINE void BeginCrouch() { Crouch(); }
	FORCEINLINE void EndCrouch() { UnCrouch(); }
	FORCEINLINE void Interact() { InteractWithActor(CastLineTrace()); };
};
