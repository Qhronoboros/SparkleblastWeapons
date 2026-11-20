// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseNode.h"
#include "../../Weapons/BaseProjectile.h"
#include "../../Upgrades/ModificationApplier.h"
#include "ShootProjectile.generated.h"

/**
 * 
 */
UCLASS()
class SPARKLEBLASTWEAPONS_API UShootProjectile : public UBaseNode
{
	GENERATED_BODY()

protected:
	// Spawns a projectile and set member variables of projectile
	virtual ENodeStatus Update() override;

private:
	// Blackboard key for Modification Applier
	UPROPERTY(EditAnywhere)
	FName DamageBlackboardKey = FName("BulletDamage");

	// Blackboard key for Modification Applier
	UPROPERTY(EditAnywhere)
	FName SpeedBlackboardKey = FName("ProjectileSpeed");

	// Base damage value
	UPROPERTY(EditAnywhere)
	float Damage = 0.0f;

	// Base projectile speed value
	UPROPERTY(EditAnywhere)
	float Speed = 3000.0f;

	// The minimum possible projectile speed
	UPROPERTY(EditAnywhere)
	float MinimumSpeed = 100.0f;

	// Projectile that gets spawned
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseProjectile> Projectile;
};
