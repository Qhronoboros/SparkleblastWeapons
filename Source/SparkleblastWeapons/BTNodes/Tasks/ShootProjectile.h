// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseNode.h"
#include "../../BaseProjectile.h"
#include "../../ModificationApplier.h"
#include "ShootProjectile.generated.h"

/**
 * 
 */
UCLASS()
class SPARKLEBLASTWEAPONS_API UShootProjectile : public UBaseNode
{
	GENERATED_BODY()

protected:
	virtual ENodeStatus Update() override;

private:
	UPROPERTY(EditAnywhere)
	FName DamageBlackboardKey = FName("BulletDamage");

	UPROPERTY(EditAnywhere)
	FName SpeedBlackboardKey = FName("ProjectileSpeed");

	UPROPERTY(EditAnywhere)
	float Damage = 0.0f;

	UPROPERTY(EditAnywhere)
	float Speed = 3000.0f;

	UPROPERTY(EditAnywhere)
	float MinimumSpeed = 100.0f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseProjectile> Projectile;
};
