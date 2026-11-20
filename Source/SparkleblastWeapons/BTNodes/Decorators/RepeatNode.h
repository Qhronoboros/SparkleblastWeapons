// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DecoratorNode.h"
#include "../../Upgrades/ModificationApplier.h"
#include "RepeatNode.generated.h"

/**
 * 
 */
UCLASS()
class SPARKLEBLASTWEAPONS_API URepeatNode : public UDecoratorNode
{
	GENERATED_BODY()

protected:
	/* Processes child multiple times in the same frame
	Stops processing if child fails or is running */
	virtual ENodeStatus Update() override;

private:
	// Blackboard key for Modification Applier
	UPROPERTY(EditAnywhere)
	FName RepeatBlackboardKey = FName("BulletsPerShot");

	// Base repeat value
	UPROPERTY(EditAnywhere)
	int RepeatAmount = 1;
};