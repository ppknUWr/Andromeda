#pragma once
#include "CharacterStats.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStats
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float MaxHealth = 100;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float MaxStamina = 100;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float MaxMana = 50;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float MaxStrength = 20;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float MaxDexterity = 20;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Basic Stats")
	float Health;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Basic Stats")
	float Stamina;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Basic Stats")
	float Mana;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float Strength;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Basic Stats")
	float Dexterity;
};
