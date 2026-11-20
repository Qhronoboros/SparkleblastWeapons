// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DecoratorNode.h"
#include "../../Upgrades/ModificationApplier.h"
#include "CooldownNode.generated.h"

UCLASS()
class SPARKLEBLASTWEAPONS_API UCooldownNode : public UDecoratorNode
{
	GENERATED_BODY()
	
public:
	// Resets TimeStarted and child
	virtual void Reset() override;

protected:
	/* Processes child over a certain time
	returns Running state when not processing child */
	virtual ENodeStatus Update() override;

private:
	// X = seconds, Y = amount of times per second
	UPROPERTY(EditAnywhere)
	UCurveFloat* CooldownCurve;

	// Blackboard key for Modification Applier
	UPROPERTY(EditAnywhere)
	FName FrequencyBlackboardKey = FName("FireRate");

	// Default is used when CooldownCurve is not set
	UPROPERTY(EditAnywhere)
	float DefaultDuration = 1.0f;

	// Gets set to time when child gets processed
	UPROPERTY(VisibleAnywhere)
	float TimeStarted = -INFINITY;
};
