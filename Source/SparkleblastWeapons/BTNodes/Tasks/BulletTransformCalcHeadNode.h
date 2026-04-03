// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseNode.h"
#include "BulletTransformCalcHeadNode.generated.h"

/**
 * 
 */
UCLASS()
class SPARKLEBLASTWEAPONS_API UBulletTransformCalcHeadNode : public UBaseNode
{
	GENERATED_BODY()

protected:
	virtual NodeStatus Update() override;

private:
	UPROPERTY(EditAnywhere)
	float BulletSpread;
};
