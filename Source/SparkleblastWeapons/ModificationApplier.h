// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ValueModifier.h"
#include "GameFramework/Actor.h"
#include "ModificationApplier.generated.h"

UCLASS()
class SPARKLEBLASTWEAPONS_API AModificationApplier : public AActor
{
	GENERATED_BODY()

public:
	float Modify(float Value);

	void AddModifier(UValueModifier* Modifier);
	void RemoveModifier(UValueModifier* Modifier);

private:
	TArray<UValueModifier*> Modifiers;
};
