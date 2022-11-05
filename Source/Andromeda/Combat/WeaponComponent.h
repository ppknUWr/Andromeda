﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponComponent.generated.h"

class AModularCharacter;
class UWeaponItem;


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ANDROMEDA_API UWeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponComponent();
	
	UPROPERTY(EditAnywhere, Instanced)
	UWeaponItem* WeaponItem;

	UFUNCTION(BlueprintPure)
	bool IsWeaponAtRest();

	UFUNCTION(BlueprintPure)
	bool IsWeaponEquipped();
	
	void EquipWeapon(AModularCharacter* ModularCharacter);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
};
