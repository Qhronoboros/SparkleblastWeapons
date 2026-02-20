// Fill out your copyright notice in the Description page of Project Settings.

#include "FMODSubsystem.h"

void UFMODSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	FMOD::Studio::System* StudioSystem = IFMODStudioModule::Get().GetStudioSystem(EFMODSystemContext::Runtime);

	if (!StudioSystem->isValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: Could not get StudioSystem"), *FString(UTF8_TO_TCHAR(__FUNCTION__)));
		return;
	}

	// Get the disc paths of all Banks
	TArray<FString> BankPaths;
	IFMODStudioModule::Get().GetAllBankPaths(BankPaths, false);

	// Get all EventDescriptions from each Bank and put them in the EventBankMap
	FMOD_STUDIO_LOAD_BANK_FLAGS flags = FMOD_STUDIO_LOAD_BANK_NORMAL;
	int PathCount = BankPaths.Num();

	for (int i = 0; i < PathCount; i++)
	{
		FMOD::Studio::Bank* Bank = nullptr;
		if (!LoadBank(StudioSystem, BankPaths[i], &Bank, false))
		{
			UE_LOG(LogTemp, Warning, TEXT("%s: Could not get Bank with path: %s"), *FString(UTF8_TO_TCHAR(__FUNCTION__)), *BankPaths[i]);
			return;
		}

		// Print BankID
		FMOD_GUID BankID;
		Bank->getID(&BankID);
		UE_LOG(LogTemp, Warning, TEXT("%s: BankID: %s"), *FString(UTF8_TO_TCHAR(__FUNCTION__)), *FMODUtils::ConvertGuid(BankID).ToString());

		// Get All EventDescriptions from Bank
		int EventCount;
		Bank->getEventCount(&EventCount);
		FMOD::Studio::EventDescription** Descriptions = new FMOD::Studio::EventDescription * [EventCount];
		FMOD_RESULT EventResult = Bank->getEventList(Descriptions, EventCount, &EventCount);

		if (EventResult != FMOD_OK)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s: Could not get EventDescriptions from GUID %s"),
					*FString(UTF8_TO_TCHAR(__FUNCTION__)),
					*FMODUtils::ConvertGuid(BankID).ToString());

			return;
		}

		// Fill EventBankMap
		for (int j = 0; j < EventCount; j++)
		{
			FMOD_GUID DescriptionFMODGuid;
			Descriptions[j]->getID(&DescriptionFMODGuid);

			EventBankMap.Emplace(FMODUtils::ConvertGuid(DescriptionFMODGuid), {BankPaths[i], BankID});
		}

		Bank->unload();
	}
	UE_LOG(LogTemp, Warning, TEXT("%s: EventBankMap Length: %d"), *FString(UTF8_TO_TCHAR(__FUNCTION__)), EventBankMap.Num());
}

void UFMODSubsystem::Deinitialize()
{
	// Deallocate structs (Causes crash so prob not needed)
	//for (TPair Pair : EventBankMap)
	//{
		//free(&Pair.Key);
		//free(&Pair.Value);
	//}

	EventBankMap.Empty();

	FMOD::Studio::System* StudioSystem = IFMODStudioModule::Get().GetStudioSystem(EFMODSystemContext::Runtime);

	// Very certain this happens automatically, but just to be sure
	StudioSystem->unloadAll();
}


FFMODEventInstance UFMODSubsystem::CreateEventInstance(const UFMODEvent* FMODEvent)
{	
	if (!FMODEvent)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: FMODEvent is not valid"), *FString(UTF8_TO_TCHAR(__FUNCTION__)));
		FMOD::Studio::EventInstance* Instance = nullptr;
		FFMODEventInstance InstanceStruct{ Instance };
		return InstanceStruct;
	}

	AutoLoadBank(FMODEvent);

	FMOD::Studio::EventDescription* Description = IFMODStudioModule::Get().GetEventDescription(FMODEvent, EFMODSystemContext::Runtime);
	FMOD::Studio::EventInstance* Instance = nullptr;
	Description->createInstance(&Instance);

	FFMODEventInstance InstanceStruct{ Instance };
	return InstanceStruct;
}

bool UFMODSubsystem::PlayEventInstance(const FFMODEventInstance EventInstance)
{
	if (!EventInstance.Instance)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: EventInstance is not valid"), *FString(UTF8_TO_TCHAR(__FUNCTION__)));
		return false;
	}

	FMOD_RESULT Result = EventInstance.Instance->start();
	if (Result != FMOD_OK)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: Failed to play event instance"), *FString(UTF8_TO_TCHAR(__FUNCTION__)));
		return false;
	}

	return true;
}

int UFMODSubsystem::GetPlaybackState(const FFMODEventInstance EventInstance)
{
	if (!EventInstance.Instance)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: Given EventInstance is not valid"), *FString(UTF8_TO_TCHAR(__FUNCTION__)));
		return 5;
	}

	FMOD_STUDIO_PLAYBACK_STATE PlaybackState;
	EventInstance.Instance->getPlaybackState(&PlaybackState);

	return PlaybackState;
}

bool UFMODSubsystem::SetMusicInstance(const FFMODEventInstance EventInstance)
{
	if (!EventInstance.Instance)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: Given EventInstance is not valid"), *FString(UTF8_TO_TCHAR(__FUNCTION__)));
		return false;
	}

	MusicInstance = EventInstance;
	return true;
}

void UFMODSubsystem::SetGlobalEventInstance(const FFMODEventInstance EventInstance, bool ShouldReplace)
{
	if (!EventInstance.Instance)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: Given EventInstance is not valid"), *FString(UTF8_TO_TCHAR(__FUNCTION__)));
		return;
	}

	FMOD::Studio::EventDescription* EventDescription = nullptr;
	EventInstance.Instance->getDescription(&EventDescription);

	FMOD_GUID EventFMODGuid;
	EventDescription->getID(&EventFMODGuid);

	FGuid EventGuid = FMODUtils::ConvertGuid(EventFMODGuid);

	FFMODEventInstance* FoundEventInstance = GlobalEventInstancesMap.Find(EventGuid);

	// If found
	if (FoundEventInstance != nullptr)
	{
		if (FoundEventInstance->Instance && !ShouldReplace)
		{
			return;
		}
		else
		{
			FoundEventInstance->Instance->release();
			GlobalEventInstancesMap.Remove(EventGuid);
		}
	}

	GlobalEventInstancesMap.Emplace(EventGuid, EventInstance);
}

FFMODEventInstance UFMODSubsystem::GetGlobalEventInstance(const UFMODEvent* FMODEvent, bool CreateNewIfEmpty)
{
	if (!FMODEvent)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: FMODEvent is not valid"), *FString(UTF8_TO_TCHAR(__FUNCTION__)));
		FMOD::Studio::EventInstance* Instance = nullptr;
		FFMODEventInstance InstanceStruct{ Instance };
		return InstanceStruct;
	}

	FFMODEventInstance* EventInstance = GlobalEventInstancesMap.Find(FMODEvent->AssetGuid);

	if (EventInstance != nullptr)
	{
		return *EventInstance;
	}

	// Creating empty EventInstance
	FFMODEventInstance NewEventInstance;
	NewEventInstance.Instance = nullptr;

	UE_LOG(LogTemp, Warning, TEXT("%s: GlobalEventInstance %s could not be found"), *FString(UTF8_TO_TCHAR(__FUNCTION__)), *FMODEvent->GetName());

	// Create new EventInstance
	if (CreateNewIfEmpty)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: Creating New EventInstance %s"), *FString(UTF8_TO_TCHAR(__FUNCTION__)), *FMODEvent->GetName());
		NewEventInstance = CreateEventInstance(FMODEvent);

		GlobalEventInstancesMap.Emplace(FMODEvent->AssetGuid, NewEventInstance);
	}

	return NewEventInstance;
}

bool UFMODSubsystem::RemoveGlobalEventInstance(const FFMODEventInstance EventInstance)
{
	FMOD::Studio::EventDescription* EventDescription = nullptr;
	EventInstance.Instance->getDescription(&EventDescription);

	FMOD_GUID EventFMODGuid;
	EventDescription->getID(&EventFMODGuid);
	FGuid EventGuid = FMODUtils::ConvertGuid(EventFMODGuid);

	FFMODEventInstance* FoundEventInstance = GlobalEventInstancesMap.Find(EventGuid);

	if (FoundEventInstance == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: GlobalEventInstance with ID %s could not be found"),
				*FString(UTF8_TO_TCHAR(__FUNCTION__)),
				*EventGuid.ToString());

		return false;
	}

	UE_LOG(LogTemp, Warning, TEXT("%s: Found GlobalEventInstance, removing"), *FString(UTF8_TO_TCHAR(__FUNCTION__)));

	FoundEventInstance->Instance->release();
	GlobalEventInstancesMap.Remove(EventGuid);
	return true;
}

void UFMODSubsystem::AutoLoadBank(const UFMODEvent* FMODEvent)
{
	if (!FMODEvent)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: FMODEvent is not valid"), *FString(UTF8_TO_TCHAR(__FUNCTION__)));
		return;
	}

	FMOD::Studio::System* StudioSystem = IFMODStudioModule::Get().GetStudioSystem(EFMODSystemContext::Runtime);

	if (!StudioSystem->isValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: Could not get StudioSystem"), *FString(UTF8_TO_TCHAR(__FUNCTION__)));
		return;
	}

	FMOD::Studio::EventDescription* Description = IFMODStudioModule::Get().GetEventDescription(FMODEvent, EFMODSystemContext::Runtime);

	if (Description->isValid())
	{
		return;
	}

	// If Description is not valid (meaning corresponding Bank is not loaded), Load Bank (This should usually not happen)
	FBankData BankData = EventBankMap[FMODEvent->AssetGuid];
	FString BankPath = BankData.Path;
	FMOD_GUID BankFMODGuid = BankData.GUID;

	UE_LOG(LogTemp, Warning, TEXT("%s: %s Bank has not been loaded yet from Event %s, now loading Bank"),
		*FString(UTF8_TO_TCHAR(__FUNCTION__)),
		*FMODUtils::LookupNameFromGuid(StudioSystem, BankFMODGuid),
		*FMODEvent->GetName());

	// Get Bank
	FMOD::Studio::Bank* Bank = nullptr;
	LoadBank(StudioSystem, BankPath, &Bank, true);
}

void UFMODSubsystem::UpdateLoadedBanks(const TSet<UFMODBank*> NewBanks)
{
	// Get Loaded Banks
	FMOD::Studio::System* StudioSystem = IFMODStudioModule::Get().GetStudioSystem(EFMODSystemContext::Runtime);

	if (!StudioSystem->isValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: Could not get StudioSystem"), *FString(UTF8_TO_TCHAR(__FUNCTION__)));
		return;
	}

	// Get Loaded Banks beforehand
	int LoadedBankCount;
	FMOD_RESULT GetBankCountResult = StudioSystem->getBankCount(&LoadedBankCount);

	FMOD::Studio::Bank** LoadedBanks = new FMOD::Studio::Bank* [LoadedBankCount];;

	// Setting default value
	FMOD_RESULT GetBanksResult = FMOD_RESULT::FMOD_ERR_FILE_NOTFOUND;
	if (GetBankCountResult == FMOD_OK)
	{
		GetBanksResult = StudioSystem->getBankList(LoadedBanks, LoadedBankCount, &LoadedBankCount);
	}

	TArray<FGuid> NewBankGuids;
	LoadNewBanks(StudioSystem, NewBanks, NewBankGuids);

	if (GetBankCountResult != FMOD_OK || GetBanksResult != FMOD_OK)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: Could not find any loaded Banks, skipping unloading"), *FString(UTF8_TO_TCHAR(__FUNCTION__)));
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("%s: LoadedBanks Length: %d"), *FString(UTF8_TO_TCHAR(__FUNCTION__)), LoadedBankCount);

	UnloadOldBanks(LoadedBanks, LoadedBankCount, NewBankGuids);
}

bool UFMODSubsystem::LoadNewBanks(FMOD::Studio::System* StudioSystem, const TSet<UFMODBank*> NewBanks, TArray<FGuid>& NewBankGuids)
{
	if (!StudioSystem->isValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: StudioSystem is invalid"), *FString(UTF8_TO_TCHAR(__FUNCTION__)));
		return false;
	}

	if (NewBanks.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: NewBanks is empty, skipping loading banks"), *FString(UTF8_TO_TCHAR(__FUNCTION__)));
		return false;
	}

	// Load Banks that have not been loaded yet
	for (UFMODBank* NewBank : NewBanks)
	{
		if (NewBank == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s: Bank is not valid, skipping"), *FString(UTF8_TO_TCHAR(__FUNCTION__)));
			continue;
		}

		// Get BankFMODGuid
		FGuid BankGuid = NewBank->AssetGuid;
		FMOD_GUID BankFMODGuid;
		FMOD::Studio::parseID(TCHAR_TO_UTF8(*BankGuid.ToString()), &BankFMODGuid);

		// Try and get loaded bank
		FMOD::Studio::Bank* Bank = nullptr;
		FMOD_RESULT GetBankResult = StudioSystem->getBankByID(&BankFMODGuid, &Bank);
		FString BankPath = IFMODStudioModule::Get().GetBankPath(*NewBank);

		// If bank not loaded
		if (GetBankResult != FMOD_OK)
		{
			// Load bank
			UE_LOG(LogTemp, Warning, TEXT("%s: Loading BankPath %s"), *FString(UTF8_TO_TCHAR(__FUNCTION__)), *BankPath);
			LoadBank(StudioSystem, BankPath, &Bank, true);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s: Already loaded BankPath %s"), *FString(UTF8_TO_TCHAR(__FUNCTION__)), *BankPath);
		}

		NewBankGuids.Emplace(BankGuid);
	}

	return true;
}

void UFMODSubsystem::UnloadOldBanks(FMOD::Studio::Bank** LoadedBanks, int LoadedBankCount, const TArray<FGuid>& NewBankGuids)
{
	// Unload Banks that are in neither NewBanks or LoadedBanks (Ignore Master Banks)
	for (int i = 0; i < LoadedBankCount; i++)
	{
		FMOD::Studio::Bank* LoadedBank = LoadedBanks[i];

		if (!LoadedBank->isValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("%s: A loaded Bank is not valid, skipping"), *FString(UTF8_TO_TCHAR(__FUNCTION__)));
			continue;
		}

		int PathBytes = 0;
		FMOD_RESULT GetPathSizeResult = LoadedBank->getPath(NULL, PathBytes, &PathBytes);

		if (GetPathSizeResult != FMOD_OK)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s: GetPathSizeResult not succeeded, skipping"), *FString(UTF8_TO_TCHAR(__FUNCTION__)));
			continue;
		}

		//UE_LOG(LogTemp, Warning, TEXT("%s: PathBytes %d"), *FString(UTF8_TO_TCHAR(__FUNCTION__)), PathBytes);

		char* CharPath = new char[PathBytes];
		FMOD_RESULT GetPathResult = LoadedBank->getPath(CharPath, PathBytes, NULL);

		if (GetPathResult != FMOD_OK)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s: GetPathResult not succeeded, skipping"), *FString(UTF8_TO_TCHAR(__FUNCTION__)));
			continue;
		}

		FString Path = FString(UTF8_TO_TCHAR(CharPath));

		UE_LOG(LogTemp, Warning, TEXT("%s: Path %s"), *FString(UTF8_TO_TCHAR(__FUNCTION__)), *Path);

		// Ignore Master and Master.strings Banks
		if (Path.StartsWith("bank:/Master"))
		{
			continue;
		}

		// If FMOD_GUID of LoadedBank not in NewBankGuids, unload Bank
		if (!NewBankGuids.Contains(FMODUtils::GetID(LoadedBank)))
		{
			UE_LOG(LogTemp, Warning, TEXT("%s: Unloading Bank with path %s"), *FString(UTF8_TO_TCHAR(__FUNCTION__)), *Path);
			LoadedBank->unload();
		}

		delete(CharPath);
	}
}

bool UFMODSubsystem::LoadBank(FMOD::Studio::System* StudioSystem, const FString& BankPath, FMOD::Studio::Bank** Bank, bool LoadSampleData)
{
	if (!StudioSystem->isValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: StudioSystem is invalid"), *FString(UTF8_TO_TCHAR(__FUNCTION__)));
		return false;
	}

	FMOD_STUDIO_LOAD_BANK_FLAGS Flags = FMOD_STUDIO_LOAD_BANK_NORMAL;
	FMOD_RESULT LoadResult = StudioSystem->loadBankFile(TCHAR_TO_UTF8(*BankPath), Flags, Bank);

	if (LoadResult != FMOD_OK)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: Failed to load bank %s: %s"),
				*FString(UTF8_TO_TCHAR(__FUNCTION__)),
				*BankPath,
				UTF8_TO_TCHAR(FMOD_ErrorString(LoadResult)));

		return false;
	}

	if (LoadSampleData)
	{
		(*Bank)->loadSampleData();
	}

	return true;
}
