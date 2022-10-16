#pragma once
#include "WeaponExpGain.generated.h"

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
