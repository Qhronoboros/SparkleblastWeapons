// Fill out your copyright notice in the Description page of Project Settings.


#include "ModificationApplier.h"

float UModificationApplier::ApplyMod(float Value)
{
	for (UValueModifier* Modifier : Modifiers)
	{
		Value = Modifier->ApplyMod(Value);
	}

	return Value;
}

void UModificationApplier::AddModifier(UValueModifier* Modifier)
{
	Modifiers.Add(Modifier);
}

void UModificationApplier::RemoveModifier(UValueModifier* Modifier)
{
	Modifiers.Remove(Modifier);
}


