#pragma once
#include "Engine/DataTable.h"
#include "CharacterStats.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStats : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float Health;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float Stamina;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float Mana;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float Strength;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float Dexterity;
};

USTRUCT(BlueprintType)
struct FWeaponExpGain
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float Sword = 10;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float Shield = 3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float Bow = 5;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float Spear = 7;
 
};
UENUM(BlueprintType)
enum class EBodyPart : uint8
{
	HEAD UMETA(DisplayName = "Head"),
	TORSO UMETA(DisplayName = "Torso"),
	ARMS UMETA(DisplayName = "Arms"),
	LEGS UMETA(DisplayName = "Legs"),
	FEET UMETA(DisplayName = "Feet"),
	COUNT UMETA(Hidden)
};

inline int GetBodyPartIndex(EBodyPart BodyPart)
{
	return static_cast<int>(BodyPart);
}