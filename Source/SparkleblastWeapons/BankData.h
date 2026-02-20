// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

struct FBankData
{
public:
	FString Path;
	FMOD_GUID GUID;

	FBankData(FString& Path, FMOD_GUID GUID) : Path(Path), GUID(GUID) {}
};
