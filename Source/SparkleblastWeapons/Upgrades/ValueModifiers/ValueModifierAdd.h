// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ValueModifier.h"
#include "Engine/DataAsset.h"
#include "ValueModifierAdd.generated.h"

/**
 * 
 */
UCLASS()
class SPARKLEBLASTWEAPONS_API UValueModifierAdd : public UValueModifier
{
	GENERATED_BODY()

public:
	virtual FString GetBlackboardKey() const override { return BlackboardKey; };

	virtual uint8 GetPriority() const override { return Priority; };

	virtual FString GetModifyDescription() const override;

	virtual float ApplyMod(float Value) const override;

private:
	UPROPERTY(EditAnywhere)
	FString BlackboardKey;

	UPROPERTY(EditAnywhere)
	uint8 Priority;

	UPROPERTY(EditAnywhere)
	float ChangingValue;
};
