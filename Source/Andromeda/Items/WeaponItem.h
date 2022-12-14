// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "WeaponItem.generated.h"

/**
 * 
 */
class UAction;
class USkeletalMesh;
class UWeaponComponent;

UENUM(BlueprintType)
enum EPreferableHand
{
	RightHand	UMETA(DisplayName = "Right Hand"),
	LeftHand	UMETA(DisplayName = "Left Hand"),
	BothHands	UMETA(DisplayName = "Both Hands")
};


UCLASS()
class ANDROMEDA_API UWeaponItem : public UItem
{
	GENERATED_BODY()
public:

	virtual void Use(AModularCharacter* Character) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (ClampMin = 0.0))
	float Damage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (ClampMin = 0.0))
	float ExpGain;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta=(GetOptions="GetWeaponAttachSocket"))
	FName WeaponAttachSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta=(GetOptions="GetWeaponRestSocket"))
	FName WeaponRestSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta=(GetOptions="GetWeapons"))
	FName WeaponStatisticName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TEnumAsByte<EPreferableHand> PreferableHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta=(EditCondition="PreferableHand == EPreferableHand::BothHands"))
	bool bIsTwoHandedWeaponForRightHand = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMesh* AttachMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UAnimMontage* EquipMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TArray<FSkeletalMaterial> SpellMaterials;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int IndexOfMaterial;
	
	UFUNCTION(BlueprintNativeEvent)
	TSubclassOf<UAction> GetActionByKey(FKey Key);
	
	UFUNCTION(BlueprintNativeEvent)
	void ButtonPressed(AModularCharacter* ModularCharacter, FKey PressedKey);
	
    UFUNCTION(BlueprintNativeEvent)
    void ButtonReleased(AModularCharacter* ModularCharacter, FKey ReleasedKey);

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	UWeaponComponent* WeaponHand;
private:
	
	UFUNCTION()
	static TArray<FName> GetWeaponAttachSocket()
	{
		return {"RightHandSocket", "LeftHandSocket", "BowSocket", "ShieldSocket"};
	}
	
	//todo: Maybe we can make rest sockets customizable by player
	UFUNCTION()
	static TArray<FName> GetWeaponRestSocket()
	{
		return {"RightHipSocket", "LeftHipSocket", "BackSocket"};
	}

public:
	UFUNCTION(BlueprintCallable)
	static TArray<FName> GetWeapons()
	{
		return {"Sword", "Warhammer", "Bow", "Spear", "Shield"};
	}
};
