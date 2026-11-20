// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ValueModifiers/ValueModifier.h"
#include "Engine/DataAsset.h"
#include "Upgrade.generated.h"

class UBlackboardComponent;
class UBlackboardData;

UCLASS(BlueprintType, EditInlineNew)
class SPARKLEBLASTWEAPONS_API UUpgrade : public UDataAsset
{
	GENERATED_BODY()

public:
	// Returns the description of the upgrade (mainly for UI)
	UFUNCTION(BlueprintPure)
	FString GetUpgradeDescription() const;

	/* Adds ValueModifiers to given blackboard
	if BlackboardKey of ValueModifier exists in given blackboard */
	UFUNCTION()
	void TransferModifiers(UBlackboardComponent* Blackboard) const;

	/* Removes ValueModifiers from given blackboard
	if BlackboardKey of ValueModifier exists in given blackboard (currently unused) */
	UFUNCTION()
	void RemoveModifiers(UBlackboardComponent* Blackboard) const;

private:
	// The ValueModifiers the upgrade contains
	UPROPERTY(EditAnywhere, Instanced)
	TArray<UValueModifier*> Modifiers;
};
