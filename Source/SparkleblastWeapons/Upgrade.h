// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ValueModifier.h"
#include "Engine/DataAsset.h"
#include "Upgrade.generated.h"

class UBlackboardComponent;
class UBlackboardData;

UCLASS( BlueprintType, EditInlineNew )
class SPARKLEBLASTWEAPONS_API UUpgrade : public UDataAsset
{
	GENERATED_BODY()

public:
	void TransferModifiers(UBlackboardComponent* Blackboard);
	void RemoveModifiers(UBlackboardComponent* Blackboard);

private:
	UPROPERTY(EditAnywhere, Instanced)
	TArray<UValueModifier*> Modifiers;
};
