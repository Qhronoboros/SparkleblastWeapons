// Fill out your copyright notice in the Description page of Project Settings.

#include "ValueModifierDivide.h"

FString UValueModifierDivide::GetModifyDescription() const
{
	return "Priority " + FString::Printf(TEXT("%d"), Priority) + " - " +
		BlackboardKey + " /" + FString::SanitizeFloat(ChangingValue);
}

float UValueModifierDivide::ApplyMod(float Value) const
{
	return ChangingValue != 0.0f ? Value / ChangingValue : ChangingValue;
}