// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseNode.h"
#include "ShootHitscanNode.generated.h"

/**
 * 
 */
UCLASS()
class SPARKLEBLASTWEAPONS_API UShootHitscanNode : public UBaseNode
{
	GENERATED_BODY()

protected:
	virtual NodeStatus Update() override;

	UPROPERTY(EditAnywhere)
	bool ShowDebugLine;

	UPROPERTY(EditAnywhere)
	float DebugLineDuration;

	UPROPERTY(EditAnywhere)
	bool PrintHitscan;

	bool LineTraceHitscan(
		const UWorld* World,
		const FVector StartLocation,
		const FVector Direction,
		const float MaxDistance,
		TArray<FHitResult>& Hits,
		const bool Piercing);
};
