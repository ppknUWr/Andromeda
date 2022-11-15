#pragma once
#include "Engine/DataTable.h"
#include "CharacterStats.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStats : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float Health=0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float Stamina=0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float Mana=0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float Strength=0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float Dexterity=0;
};

USTRUCT(BlueprintType)
struct FWeaponExpGain
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float Sword = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float Shield = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float Bow = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float Spear = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float Warhammer = 0;
 
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

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	IDLE UMETA(DisplayName = "Idle"), 
	ATTACK UMETA(DisplayName = "Attack"), 
	DEFFEND UMETA(DisplayName = "Deffend"), 
	GRAB UMETA(DisplayName = "Grab"), 
	USE UMETA(DisplayName = "Use"), 
	EQUIP UMETA(DisplayName = "Equip"), 
	COUNT UMETA(Hidden)
};

inline int GetBodyPartIndex(EBodyPart BodyPart)
{
	return static_cast<int>(BodyPart);
}