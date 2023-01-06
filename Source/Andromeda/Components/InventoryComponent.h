// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UItem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANDROMEDA_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	bool AddItem(UItem* Item);

	UFUNCTION(BlueprintCallable)
	bool RemoveItem(UItem* Item);

	UFUNCTION(BlueprintCallable)
	bool ExchangeItem(UItem* Item, UInventoryComponent* otherInventory);

public:

	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<UItem*> DefaultItems;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	int32 Capacity;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Items", SaveGame)
	TArray<UItem*> Items;
	
};
