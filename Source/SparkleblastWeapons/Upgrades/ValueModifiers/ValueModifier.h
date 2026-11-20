// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ValueModifier.generated.h"

UCLASS(EditInlineNew, BlueprintType, abstract)
class SPARKLEBLASTWEAPONS_API UValueModifier : public UDataAsset
{
	GENERATED_BODY()

public:
	// Returns the BlackboardKey the ValueModifier should add/remove itself to
	UFUNCTION()
	virtual FString GetBlackboardKey() const PURE_VIRTUAL(UValueModifier::GetBlackboardKey, return "";);

	// Get the priority for sorting (lowest to highest)
	UFUNCTION()
	virtual uint8 GetPriority() const PURE_VIRTUAL(UValueModifier::GetPriority, return MAX_uint8;);

	// Get the modify description (mainly for UI)
	UFUNCTION()
	virtual FString GetModifyDescription() const PURE_VIRTUAL(UValueModifier::GetModifyDescription, return "";);

	// Applies the value modification to given value and returns the result
	UFUNCTION()
	virtual float ApplyMod(float Value) const PURE_VIRTUAL(UValueModifier::ApplyMod, return Value;);
};
