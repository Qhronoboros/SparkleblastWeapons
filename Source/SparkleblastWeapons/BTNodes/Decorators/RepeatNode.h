// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DecoratorNode.h"
#include "../../ModificationApplier.h"
#include "RepeatNode.generated.h"

/**
 * 
 */
UCLASS()
class SPARKLEBLASTWEAPONS_API URepeatNode : public UDecoratorNode
{
	GENERATED_BODY()

protected:
	virtual ENodeStatus Update() override;

private:
	UPROPERTY(EditAnywhere)
	FName RepeatBlackboardKey = FName("BulletsPerShot");

	UPROPERTY(EditAnywhere)
	int RepeatAmount = 1;
};