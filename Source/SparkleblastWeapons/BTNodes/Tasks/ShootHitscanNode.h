// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseNode.h"
#include "../../Upgrades/ModificationApplier.h"
#include "ShootHitscanNode.generated.h"

/**
 * 
 */
UCLASS()
class SPARKLEBLASTWEAPONS_API UShootHitscanNode : public UBaseNode
{
	GENERATED_BODY()

protected:
	// Trace a ray and deal damage to targets hit by ray
	virtual ENodeStatus Update() override;

private:
	// Blackboard key for Modification Applier
	UPROPERTY(EditAnywhere)
	FName DamageBlackboardKey = FName("BulletDamage");

	// Base damage value
	UPROPERTY(EditAnywhere)
	float Damage = 0.0f;

	// Whether to show debug line of ray
	UPROPERTY(EditAnywhere)
	bool ShowDebugLine = true;

	// Duration of debug line
	UPROPERTY(EditAnywhere)
	float DebugLineDuration = 0.25f;

	// Whether to print the result of hitscan
	UPROPERTY(EditAnywhere)
	bool PrintHitscan = false;

	/* When piercing, receive multiple hits from linetrace
	When not piercing, only receive one hit from linetrace */
	UFUNCTION()
	bool LineTraceHitscan(
		const UWorld* World,
		const FVector StartLocation,
		const FVector Direction,
		const float MaxDistance,
		TArray<FHitResult>& Hits,
		const bool Piercing) const;
};
