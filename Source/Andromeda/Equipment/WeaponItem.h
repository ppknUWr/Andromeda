// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0))
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	USkeletalMesh* AttachMesh;

	UFUNCTION(BlueprintImplementableEvent)
	void LeftMouseClick(USkeletalMeshComponent* MeshComponent);
	
};
