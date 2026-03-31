// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseNode.h"
#include "BulletTransformCalcAccurateNode.generated.h"

/**
 * 
 */
UCLASS()
class SPARKLEBLASTWEAPONS_API UBulletTransformCalcAccurateNode : public UBaseNode
{
	GENERATED_BODY()

protected:
	virtual NodeStatus Update() override;

	bool GetLineTraceHit(UWorld* World, FVector location, FVector direction, float MaxDistance, FHitResult& hit);
};
