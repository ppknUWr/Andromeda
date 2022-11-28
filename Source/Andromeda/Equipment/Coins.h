// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Coins.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ANDROMEDA_API UCoins : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCoins();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coins")
	int32 Coins;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Coins")
	UTexture2D* Thumbnail;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

		
};
