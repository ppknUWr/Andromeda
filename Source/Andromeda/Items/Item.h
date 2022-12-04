// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"


class AModularCharacter;
class UInventoryComponent;


UENUM(BlueprintType)
enum class EItemType : uint8
{
	WEAPON UMETA(DisplayName = "Weapon"),
	RESOURCE UMETA(DisplayName = "Resource"),
	POTION UMETA(DisplayName = "Potion"),
	OTHER UMETA(DisplayName = "Other")
};

UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class ANDROMEDA_API UItem : public UObject
{
	GENERATED_BODY()

public:
	
	UItem();

	virtual UWorld* GetWorld() const { return World; };

	// Delete pure virtual for now.

	virtual void Use(AModularCharacter* Character);

	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(AModularCharacter* Character);

public:

	UPROPERTY(Transient)
	UWorld* World;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta=(GetOptions="GetActionText"))
	FText UseActionText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	EItemType ItemType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	UStaticMesh* PickupMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	UTexture2D* Thumbnail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText ItemDisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0))
	float Weight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	int SellPrice;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	int BuyPrice;

	UPROPERTY()
	UInventoryComponent* OwningInventory;

protected:

	UFUNCTION()
	TArray<FText> GetActionText() const;
};
