// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ValueModifiers/ValueModifier.h"
#include "Engine/DataAsset.h"
#include "ModificationApplier.generated.h"

UCLASS(BlueprintType)
class SPARKLEBLASTWEAPONS_API UModificationApplier : public UDataAsset
{
	GENERATED_BODY()

public:
	// Applies ValueModifiers in order to given value and returns the result
	UFUNCTION()
	float ApplyMod(float Value);

	// Add ValueModifier to array and sort using Value Modifier's priority value (lowest to highest)
	UFUNCTION()
	void AddModifier(UValueModifier* Modifier);

	// Remove ValueModifier from array
	UFUNCTION()
	void RemoveModifier(UValueModifier* Modifier);

private:
	// Array of ValueModifiers that will collectively modify a value in order
	UPROPERTY()
	TArray<UValueModifier*> Modifiers;
};
