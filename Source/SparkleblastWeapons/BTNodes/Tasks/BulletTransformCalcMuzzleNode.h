// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseNode.h"
#include "BulletTransformCalcMuzzleNode.generated.h"

/**
 * 
 */
UCLASS()
class SPARKLEBLASTWEAPONS_API UBulletTransformCalcMuzzleNode : public UBaseNode
{
	GENERATED_BODY()

protected:
	virtual NodeStatus Update() override;
};
