// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.generated.h"

/**
 * 
 */
class AModularCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActionStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActionInterrupted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActionFinished);

UCLASS(Blueprintable, BlueprintType)
class ANDROMEDA_API UAction : public UObject
{
	GENERATED_BODY()

public:

	UAction();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanBeInterrupted = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanInterruptAction = false;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartAction(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StopAction(AActor* Instigator);

	UPROPERTY(BlueprintAssignable)
	FOnActionStarted ActionStarted;
	
	UPROPERTY(BlueprintAssignable)
	FOnActionInterrupted ActionInterrupted;
	
	UPROPERTY(BlueprintAssignable)
	FOnActionFinished ActionFinished;
	
	UFUNCTION(BlueprintNativeEvent)
	void SetAdditionalParams(const TMap<FName, UObject*>& AdditionalObjects);
	
protected:
	UPROPERTY(BlueprintReadWrite)
	AModularCharacter* ModularCharacter;
};
