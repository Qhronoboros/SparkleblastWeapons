// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DecoratorNode.h"
#include "../../ModificationApplier.h"
#include "CooldownNode.generated.h"

//class FBlackboardKeySelector;
/**
 * 
 */
UCLASS()
class SPARKLEBLASTWEAPONS_API UCooldownNode : public UDecoratorNode
{
	GENERATED_BODY()
	
public:
	virtual void Reset() override;

protected:
	virtual ENodeStatus Update() override;

private:
	// X = seconds, Y = amount of times per second
	UPROPERTY(EditAnywhere)
	UCurveFloat* CooldownCurve;

	UPROPERTY(EditAnywhere)
	FName FrequencyBlackboardKey = FName("FireRate");

	UPROPERTY(EditAnywhere)
	float DefaultDuration = 1.0f;

	UPROPERTY(VisibleAnywhere)
	float TimeStarted = -INFINITY;
};
