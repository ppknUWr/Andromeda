 // Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Andromeda/Items/Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	Capacity = 20;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();


	for (const auto& Item : DefaultItems)
	{
		AddItem(Item);
	}
	// ...
	
}

bool UInventoryComponent::AddItem(UItem* Item)
{
	if (Items.Num() >= Capacity || Item == nullptr)
	{
		return false;
	}

	Item->OwningInventory = this;
	Item->World = GetWorld();
	Items.Add(Item);

	OnInventoryUpdated.Broadcast();

	return true;
}

bool UInventoryComponent::RemoveItem(UItem* Item)
{
	if (Item)
	{
		Item->OwningInventory = nullptr;
		Item->World = nullptr;
		Items.RemoveSingle(Item);

		OnInventoryUpdated.Broadcast();

		return true;
	}

	return false;
}