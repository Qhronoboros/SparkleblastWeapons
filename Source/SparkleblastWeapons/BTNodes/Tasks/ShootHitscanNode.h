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
	virtual ENodeStatus Update() override;

private:
	UPROPERTY(EditAnywhere)
	FName DamageBlackboardKey = FName("BulletDamage");

	UPROPERTY(EditAnywhere)
	float Damage = 0.0f;

	UPROPERTY(EditAnywhere)
	bool ShowDebugLine = true;

	UPROPERTY(EditAnywhere)
	float DebugLineDuration = 0.25f;

	UPROPERTY(EditAnywhere)
	bool PrintHitscan = false;

	UFUNCTION()
	bool LineTraceHitscan(
		const UWorld* World,
		const FVector StartLocation,
		const FVector Direction,
		const float MaxDistance,
		TArray<FHitResult>& Hits,
		const bool Piercing) const;
};
