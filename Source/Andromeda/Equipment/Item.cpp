// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

UItem::UItem()
{
	UseActionText = FText::FromString("Use");
	ItemDisplayName = FText::FromString("Item");
	ItemDescription = FText::FromString("Basic Item Description");
	Weight = 1.f;

	
}

TArray<FText> UItem::GetActionText() const
{
	return { FText::FromString("Use"), FText::FromString("Grab")};
}
