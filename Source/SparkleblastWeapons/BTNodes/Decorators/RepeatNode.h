// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DecoratorNode.h"
#include "RepeatNode.generated.h"

/**
 * 
 */
UCLASS()
class SPARKLEBLASTWEAPONS_API URepeatNode : public UDecoratorNode
{
	GENERATED_BODY()

protected:
	virtual NodeStatus Update() override;

private:
	UPROPERTY(EditAnywhere)
	FString RepeatBlackboardKey;

	UPROPERTY(EditAnywhere)
	int DefaultRepeat;
};