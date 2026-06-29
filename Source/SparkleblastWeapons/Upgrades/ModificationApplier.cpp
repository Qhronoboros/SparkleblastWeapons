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
	
	Modifiers.Sort([](const UValueModifier& a, const UValueModifier& b) {
			return a.GetPriority() < b.GetPriority();
	});
}

void UModificationApplier::RemoveModifier(UValueModifier* Modifier)
{
	Modifiers.Remove(Modifier);
}


