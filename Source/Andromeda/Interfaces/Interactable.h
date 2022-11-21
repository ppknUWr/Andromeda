// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
//#include "../Character/ModularCharacter.h"
#include "Interactable.generated.h"

//forward declaration
class AModularCharacter;

// This class does not need to be modified.
UINTERFACE()
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ANDROMEDA_API IInteractable
{
	GENERATED_BODY()
	

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool CanBeInteractedWith(AModularCharacter* Character);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Interact(AModularCharacter* Character);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void IsNoLongerLookedAt(AModularCharacter* Character);
};
