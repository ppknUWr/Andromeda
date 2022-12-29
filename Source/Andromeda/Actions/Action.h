// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Action.generated.h"

/**
 * 
 */
class AModularCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActionStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActionInterrupted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActionFinished);

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
	void OnKeyPressed(FKey Key);
	
	UFUNCTION(BlueprintNativeEvent)
    void OnKeyReleased(FKey Key);

	UFUNCTION(BlueprintNativeEvent)
	void StopAction(AActor* Instigator);

	UPROPERTY(BlueprintAssignable)
	FOnActionStarted ActionStarted;
	
	UPROPERTY(BlueprintAssignable)
	FOnActionInterrupted ActionInterrupted;
	
	UPROPERTY(BlueprintAssignable)
	FOnActionFinished ActionFinished;

protected:
	UPROPERTY(BlueprintReadWrite)
	AModularCharacter* ModularCharacter;
};
