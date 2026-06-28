// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ValueModifier.h"
#include "Engine/DataAsset.h"
#include "ModificationApplier.generated.h"

UCLASS(BlueprintType)
class SPARKLEBLASTWEAPONS_API UModificationApplier : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION()
	float ApplyMod(float Value);

	UFUNCTION()
	void AddModifier(UValueModifier* Modifier);

	UFUNCTION()
	void RemoveModifier(UValueModifier* Modifier);

private:
	UPROPERTY()
	TArray<UValueModifier*> Modifiers;
};
