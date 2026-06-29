// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Projectile.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UProjectile : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SPARKLEBLASTWEAPONS_API IProjectile
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Constructor(const float AttackDamage, const float Speed, const bool Piercing, AActor* Shooter);
};
