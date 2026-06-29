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
	UFUNCTION(BlueprintPure)
	FString GetUpgradeDescription() const;

	UFUNCTION()
	void TransferModifiers(UBlackboardComponent* Blackboard) const;

	UFUNCTION()
	void RemoveModifiers(UBlackboardComponent* Blackboard) const;

private:
	UPROPERTY(EditAnywhere, Instanced)
	TArray<UValueModifier*> Modifiers;
};
