// Fill out your copyright notice in the Description page of Project Settings.

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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWeaponItem* WeaponItem = nullptr;

	UFUNCTION(BlueprintPure)
	bool IsWeaponAtRest();

	UFUNCTION(BlueprintPure)
	bool IsWeaponEquipped();

	UFUNCTION(BlueprintCallable)
	void ChangeWeapon(UWeaponItem* NewWeapon);
	
	void PlayEquipAnimation(AModularCharacter* ModularCharacter);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	FORCEINLINE bool IsWeaponValid() const { return (WeaponItem != nullptr); }
};
