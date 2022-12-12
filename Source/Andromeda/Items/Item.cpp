// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "../Character/ModularCharacter.h"

UItem::UItem()
{
	UseActionText = FText::FromString("Use");
	ItemDisplayName = FText::FromString("Item");
	ItemDescription = FText::FromString("Basic Item Description");
	Weight = 1.f;
	ItemType = EItemType::OTHER;
	BuyPrice = 100;
	SellPrice = 25;
}

void UItem::Use(AModularCharacter* Character)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Blue, "Item used");
}

TArray<FText> UItem::GetActionText() const
{
	return { FText::FromString("Use"), FText::FromString("Grab")};
}
