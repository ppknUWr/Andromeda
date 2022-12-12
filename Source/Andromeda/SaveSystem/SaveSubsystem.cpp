// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSubsystem.h"

#include "EngineUtils.h"
#include "SaveableInterface.h"
#include "AndromedaSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"


void USaveSubsystem::WriteSaveGame()
{
	// Clear arrays, may contain data from previously loaded SaveGame
	CurrentSaveGame->SavedActors.Empty();

	AGameStateBase* GS = GetWorld()->GetGameState();
	if (GS == nullptr)
	{
		// Warn about failure to save?
		return;
	}
	
	
	// Iterate the entire world of actors
	for (FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		// Only interested in our 'gameplay actors', skip actors that are being destroyed
		// Note: You might instead use a dedicated SavableObject interface for Actors you want to save instead of re-using GameplayInterface
		if (!IsValid(Actor) || !Actor->Implements<USaveableInterface>())
		{
			continue;
		}

		FActorSaveData ActorData;
		ActorData.ActorName = Actor->GetFName();
		ActorData.Transform = Actor->GetActorTransform();
		
		// Pass the array to fill with data from Actor
		FMemoryWriter MemWriter(ActorData.ByteData);

		FObjectAndNameAsStringProxyArchive Ar(MemWriter, true);
		// Find only variables with UPROPERTY(SaveGame)
		Ar.ArIsSaveGame = true;
		// Converts Actor's SaveGame UPROPERTIES into binary array
		Actor->Serialize(Ar);

		for(auto& Component:Actor->GetComponents())
		{
			Component->Serialize(Ar);
		}

		CurrentSaveGame->SavedActors.Add(ActorData);
	}

	UGameplayStatics::SaveGameToSlot(CurrentSaveGame, CurrentSlotName, 0);
	
}


void USaveSubsystem::LoadSaveGame(FString InSlotName /*= ""*/)
{
	
	if (UGameplayStatics::DoesSaveGameExist(InSlotName, 0))
	{
		CurrentSaveGame = Cast<UAndromedaSaveGame>(UGameplayStatics::LoadGameFromSlot(InSlotName, 0));
		if (CurrentSaveGame == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to load SaveGame Data."));
			return;
		}

		UE_LOG(LogTemp, Log, TEXT("Loaded SaveGame Data."));


		// Iterate the entire world of actors
		for (FActorIterator It(GetWorld()); It; ++It)
		{
			AActor* Actor = *It;
			// Only interested in our 'gameplay actors'
			if (!Actor->Implements<USaveableInterface>())
			{
				continue;
			}

			for (FActorSaveData ActorData : CurrentSaveGame->SavedActors)
			{
				if (ActorData.ActorName == Actor->GetFName())
				{
					Actor->SetActorTransform(ActorData.Transform);

					FMemoryReader MemReader(ActorData.ByteData);

					FObjectAndNameAsStringProxyArchive Ar(MemReader, true);
					Ar.ArIsSaveGame = true;
					// Convert binary array back into actor's variables
					Actor->Serialize(Ar);
				
					Cast<ISaveableInterface>(Actor)->OnActorLoaded();

					break;
				}
			}
		}
	}
	else
	{
		CurrentSaveGame = Cast<UAndromedaSaveGame>(UGameplayStatics::CreateSaveGameObject(UAndromedaSaveGame::StaticClass()));

		UE_LOG(LogTemp, Log, TEXT("Created New SaveGame Data."));
	}
}

void USaveSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CurrentSaveGame = Cast<UAndromedaSaveGame>(UGameplayStatics::CreateSaveGameObject(UAndromedaSaveGame::StaticClass()));
}
