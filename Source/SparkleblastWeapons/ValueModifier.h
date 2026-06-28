// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArithmeticOperator.h"
#include "Engine/DataAsset.h"
#include "ValueModifier.generated.h"

UCLASS( EditInlineNew )
class SPARKLEBLASTWEAPONS_API UValueModifier : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	FString BlackboardKey;

	UPROPERTY(EditAnywhere)
	int Priority;

	UFUNCTION()
	FString GetModifyDescription();

	UFUNCTION()
	float ApplyMod(float Value);

private:
	UPROPERTY(EditAnywhere)
	EArithmeticOperator Operator;

	UPROPERTY(EditAnywhere)
	float ChangingValue;
};
