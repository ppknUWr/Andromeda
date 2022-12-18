// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Action.generated.h"

/**
 * 
 */
class UAction;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActionStarted, UAction*, Action);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActionInterrupted, UAction*, Action);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActionFinished, UAction*, Action);

UCLASS()
class ANDROMEDA_API UAction : public UObject
{
	GENERATED_BODY()

public:

	UAction();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanBeInterrupted = false;

	UFUNCTION(BlueprintNativeEvent)
	void StartAction(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent)
	void StopAction(AActor* Instigator);

	UPROPERTY(BlueprintAssignable)
	FOnActionStarted ActionStarted;
	
	UPROPERTY(BlueprintAssignable)
	FOnActionInterrupted ActionInterrupted;
	
	UPROPERTY(BlueprintAssignable)
	FOnActionFinished ActionFinished;
};
