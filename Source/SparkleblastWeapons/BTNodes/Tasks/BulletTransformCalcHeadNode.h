// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseNode.h"
#include "../../ModificationApplier.h"
#include "BulletTransformCalcHeadNode.generated.h"

/**
 * 
 */
UCLASS()
class SPARKLEBLASTWEAPONS_API UBulletTransformCalcHeadNode : public UBaseNode
{
	GENERATED_BODY()

protected:
	virtual ENodeStatus Update() override;

private:
	UPROPERTY(EditAnywhere)
	FName BulletSpreadBlackboardKey = FName("BulletSpread");

	UPROPERTY(EditAnywhere)
	float BulletSpread = 0.0f;
};
