// Fill out your copyright notice in the Description page of Project Settings.

#include "ValueModifierAdd.h"

FString UValueModifierAdd::GetModifyDescription() const
{
	return "Priority " + FString::Printf(TEXT("%d"), Priority) + " - " +
		BlackboardKey + " +" + FString::SanitizeFloat(ChangingValue);
}

float UValueModifierAdd::ApplyMod(float Value) const
{
	return Value + ChangingValue;
}