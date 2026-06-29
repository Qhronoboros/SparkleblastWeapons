// Fill out your copyright notice in the Description page of Project Settings.

#include "ValueModifierSubtract.h"

FString UValueModifierSubtract::GetModifyDescription() const
{
	return "Priority " + FString::Printf(TEXT("%d"), Priority) + " - " +
		BlackboardKey + " -" + FString::SanitizeFloat(ChangingValue);
}

float UValueModifierSubtract::ApplyMod(float Value) const
{
	return Value - ChangingValue;
}