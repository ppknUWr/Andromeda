// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "WeaponAction.generated.h"

/**
 * 
 */

class UWeaponComponent;

UCLASS()
class ANDROMEDA_API UWeaponAction : public UAction
{
	GENERATED_BODY()

public:

	UWeaponAction();

	virtual void SetAdditionalParams_Implementation(const TMap<FName, UObject*>& AdditionalObjects) override;

	

protected:
	UFUNCTION()
	virtual void FinishedMontageInternal(UAnimMontage* AnimMontage, bool bInterrupted);

	UPROPERTY()
	UWeaponComponent* WeaponComponent;

	
	FOnMontageBlendingOutStarted MontageBlendingOutStarted;	
};
