// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionComponent.generated.h"

class UAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANDROMEDA_API UActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActionComponent();

	UFUNCTION(BlueprintCallable)
	UAction* AddAction(TSubclassOf<UAction> NewActionClass, TMap<FName, UObject*> AdditionalObjects, bool bForceInterrupt = false);

	
protected:

	UPROPERTY(VisibleAnywhere, Transient)
	UAction* CurrentAction = nullptr;

	UPROPERTY(VisibleAnywhere, Transient)
	UAction* QueuedAction = nullptr;

	UFUNCTION(BlueprintCallable)
	void StartAction();

	UFUNCTION()
	void ActionStopped();
	
public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UAction* GetCurrentAction() const { return CurrentAction; }
		
};
