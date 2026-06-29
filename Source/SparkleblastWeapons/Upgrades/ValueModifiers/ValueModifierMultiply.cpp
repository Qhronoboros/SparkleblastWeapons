// Fill out your copyright notice in the Description page of Project Settings.

#include "ValueModifierMultiply.h"

FString UValueModifierMultiply::GetModifyDescription() const
{
	return "Priority " + FString::Printf(TEXT("%d"), Priority) + " - " +
		BlackboardKey + " x" + FString::SanitizeFloat(ChangingValue);
}

float UValueModifierMultiply::ApplyMod(float Value) const
{
	return Value * ChangingValue;
}