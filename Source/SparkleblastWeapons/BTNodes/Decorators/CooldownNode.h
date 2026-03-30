// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DecoratorNode.h"
#include "CooldownNode.generated.h"

/**
 * 
 */
UCLASS()
class SPARKLEBLASTWEAPONS_API UCooldownNode : public UDecoratorNode
{
	GENERATED_BODY()
	
public:
	virtual void SetupBlackboard(UBlackboardComponent* NewBlackboard) override;
	virtual void Reset() override;

protected:
	virtual NodeStatus Update() override;

private:
	UPROPERTY(EditAnywhere)
	float Duration;

	UPROPERTY(VisibleAnywhere)
	double TimeStarted = 0.0;
};
