// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SaveSubsystem.generated.h"


class UAndromedaSaveGame;
/**
 * 
 */


UCLASS(meta=(DisplayName="SaveGame System"))
class ANDROMEDA_API USaveSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintCallable, Category = "SaveGame" )
	void WriteSaveGame();

	/* Load from disk, optional slot name */
	UFUNCTION(BlueprintCallable, Category = "SaveGame" )
	void LoadSaveGame(FString InSlotName = "Slot_01");

	/* Initialize Subsystem, for load in SaveGameSettings variables */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UPROPERTY()
	UAndromedaSaveGame* CurrentSaveGame;

	UPROPERTY()
	FString CurrentSlotName = "Slot_01";


	
};
