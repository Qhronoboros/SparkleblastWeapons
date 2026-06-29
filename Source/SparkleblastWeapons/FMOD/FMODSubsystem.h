// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FMODEvent.h"
#include "FMODBank.h"
#include "FMODBlueprintStatics.h"
#include "FMODSettings.h"
#include <AssetRegistry/AssetRegistryModule.h>
#include "fmod_errors.h"
#include "BankData.h"
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FMODSubsystem.generated.h"

UCLASS()
class SPARKLEBLASTWEAPONS_API UFMODSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FFMODEventInstance MusicInstance;

	UPROPERTY(BlueprintReadWrite)
	TMap<FGuid, FFMODEventInstance> GlobalEventInstancesMap;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// Creates an EventInstance and Loads corresponding Bank if Bank is not loaded yet
	UFUNCTION(BlueprintCallable)
	FFMODEventInstance CreateEventInstance(const UFMODEvent* FMODEvent);

	// Plays the given EventInstance (FMOD has this, but it automatically releases the EventInstance, which is not desirable)
	UFUNCTION(BlueprintCallable)
	bool PlayEventInstance(const FFMODEventInstance EventInstance);

	// Returns the PlaybackState of the given EventInstance
	UFUNCTION(BlueprintCallable)
	int GetPlaybackState(const FFMODEventInstance EventInstance);

	// Sets the MusicInstance
	UFUNCTION(BlueprintCallable)
	bool SetMusicInstance(const FFMODEventInstance EventInstance);

	// Add a Global EventInstance to the GlobalEventInstancesMap, if there already is an occurance and ShouldReplace is true, replace it
	UFUNCTION(BlueprintCallable)
	void SetGlobalEventInstance(const FFMODEventInstance EventInstance, bool ShouldReplace);

	// Get the Global EventInstance, if not found and CreateNewIfEmpty is true, create a new GlobalEventInstance and return it
	UFUNCTION(BlueprintPure)
	FFMODEventInstance GetGlobalEventInstance(const UFMODEvent* FMODEvent, bool CreateNewIfEmpty = true);

	// Remove a Global EventInstance if there is one
	UFUNCTION(BlueprintCallable)
	bool RemoveGlobalEventInstance(const FFMODEventInstance EventInstance);

	// Load Bank of corresponding Event if Bank has not been loaded yet
	UFUNCTION(BlueprintCallable)
	void AutoLoadBank(const UFMODEvent* FMODEvent);

	// Load Banks that are in New Banks that have not been loaded yet and unload banks that are not in the New Banks
	UFUNCTION(BlueprintCallable)
	void UpdateLoadedBanks(const TSet<UFMODBank*> NewBanks);

private:
	// Map of Events FGUID as keys and Bank struct with Disc Path and FMOD_GUID as values
	TMap<FGuid, FBankData> EventBankMap;

	// Load Banks in NewBanks that have not been loaded yet and emplace every Bank FGuid inside NewBankGuids
	bool LoadNewBanks(FMOD::Studio::System* StudioSystem, const TSet<UFMODBank*> NewBanks, TArray<FGuid>& NewBankGuids);

	// Unload Banks that are in neither NewBankGuids or LoadedBanks (Ignore Master Banks)
	void UnloadOldBanks(FMOD::Studio::Bank** LoadedBanks, int LoadedBankCount, const TArray<FGuid>& NewBankGuids);

	// Load Bank using BankPath
	bool LoadBank(FMOD::Studio::System* StudioSystem, const FString& BankPath, FMOD::Studio::Bank** Bank, bool LoadSampleData);
};