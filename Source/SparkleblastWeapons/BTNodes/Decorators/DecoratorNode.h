// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseNode.h"
#include "DecoratorNode.generated.h"

// Not used by itself, but used for inheritance
UCLASS()
class SPARKLEBLASTWEAPONS_API UDecoratorNode : public UBaseNode
{
	GENERATED_BODY()

public:
	// Set given blackboard for itself and child
	virtual void SetupBlackboard(UBlackboardComponent* NewBlackboard) override;
	// Resets child
	virtual void Reset() override;

protected:
	UPROPERTY(EditAnywhere, Instanced)
	UBaseNode* Child;

	virtual ENodeStatus Update() override;
};
