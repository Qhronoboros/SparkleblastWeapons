// Fill out your copyright notice in the Description page of Project Settings.


#include "ModificationApplier.h"

float AModificationApplier::Modify(float Value)
{
	for (UValueModifier* Modifier : Modifiers)
	{
		Value = Modifier->Modify(Value);
	}

	return Value;
}

void AModificationApplier::AddModifier(UValueModifier* Modifier)
{
	Modifiers.Add(Modifier);
}

void AModificationApplier::RemoveModifier(UValueModifier* Modifier)
{
	Modifiers.Remove(Modifier);
}


