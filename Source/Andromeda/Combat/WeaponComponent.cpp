// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"

#include "Andromeda/Equipment/WeaponItem.h"


// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	if(WeaponItem)
	{
		SetSkeletalMesh(WeaponItem->AttachMesh);
	}
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	if(WeaponItem)
	{
		SetSkeletalMesh(WeaponItem->AttachMesh);
	}
}
