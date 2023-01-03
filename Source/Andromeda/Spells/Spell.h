// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spell.generated.h"

UCLASS()
class ANDROMEDA_API ASpell : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpell();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraSystem* SpellEffect = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraComponent* SpellComponent = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
