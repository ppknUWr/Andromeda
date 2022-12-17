// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponItem.h"
#include "SideArmsWeaponItem.generated.h"

/**
 * 
 */
UCLASS()
class ANDROMEDA_API USideArmsWeaponItem : public UWeaponItem
{
	GENERATED_BODY()

public:

	virtual void MouseButtonPressed_Implementation(AModularCharacter* ModularCharacter, bool bIsRightHand) override;

	void AttackWithCombo(USkeletalMeshComponent* MeshComponent, int32 ComboIndex) const;
};
