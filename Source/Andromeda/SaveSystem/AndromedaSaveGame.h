// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "AndromedaSaveGame.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FActorSaveData
{
	GENERATED_BODY()

public:
	/* ID of which Actor this belongs to */
	UPROPERTY()
	FName ActorName;

	/* For movable Actors, keep location,rotation,scale. */
	UPROPERTY()
	FTransform Transform;

	/* Contains all 'SaveGame' marked variables of the Actor */
	UPROPERTY()
	TArray<uint8> ByteData;
	
};

UCLASS()
class ANDROMEDA_API UAndromedaSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FActorSaveData> SavedActors;
	

	
};
