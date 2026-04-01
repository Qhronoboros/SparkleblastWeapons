// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DecoratorNode.h"
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
	virtual NodeStatus Update() override;

private:
	UPROPERTY(EditAnywhere)
	FString DurationBlackboardKey;

	UPROPERTY(EditAnywhere)
	float DefaultDuration;

	UPROPERTY(VisibleAnywhere)
	float TimeStarted = 0.0;
};
