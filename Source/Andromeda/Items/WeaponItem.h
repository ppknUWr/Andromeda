﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Andromeda/Character/CharacterStats.h"
#include "WeaponItem.generated.h"

/**
 * 
 */
class USkeletalMesh;
class USkeletalMeshComponent;


UCLASS()
class ANDROMEDA_API UWeaponItem : public UItem
{
	GENERATED_BODY()
public:

	virtual void Use(AModularCharacter* Character) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0))
	float Damage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0))
	float ExpGain;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta=(GetOptions="GetWeaponAttachSocket"))
	FName WeaponAttachSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta=(GetOptions="GetWeaponRestSocket"))
	FName WeaponRestSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta=(GetOptions="GetWeapons"))
	FName WeaponStatisticName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	USkeletalMesh* AttachMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UAnimMontage* EquipMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UAnimMontage* AttackMontage;
	
	UFUNCTION(BlueprintImplementableEvent)
	void LeftMousePressed(USkeletalMeshComponent* MeshComponent);

	UFUNCTION(BlueprintImplementableEvent)
	void LeftMouseReleased(USkeletalMeshComponent* MeshComponent);
	
    UFUNCTION(BlueprintImplementableEvent)
    void RightMousePressed(USkeletalMeshComponent* MeshComponent);

    UFUNCTION(BlueprintImplementableEvent)
    void RightMouseReleased(USkeletalMeshComponent* MeshComponent);

	void AttackWithCombo(USkeletalMeshComponent* MeshComponent);

private:

	int32 ComboCounter = 0;

	UFUNCTION()
	static TArray<FName> GetWeaponAttachSocket()
	{
		return {"RightHandSocket", "LeftHandSocket"};
	}
	
	//todo: Maybe we can make rest sockets customizable by player
	UFUNCTION()
	static TArray<FName> GetWeaponRestSocket()
	{
		return {"RightHipSocket", "LeftHipSocket", "BackSocket"};
	}

public:
	UFUNCTION(BlueprintCallable)
	static TArray<FName> GetWeapons()
	{
		return {"Sword", "Warhammer", "Bow", "Spear", "Shield"};
	}
};
