// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseNode.h"
#include "CompositeNode.generated.h"

// Not used by itself, but used for inheritance
UCLASS()
class SPARKLEBLASTWEAPONS_API UCompositeNode : public UBaseNode
{
	GENERATED_BODY()

public:
	// Set given blackboard for itself and children
	virtual void SetupBlackboard(UBlackboardComponent* NewBlackboard) override;

	// Set the currentChild back to 0 and reset children
    virtual void Reset() override;

protected:
	UPROPERTY(EditAnywhere, Instanced)
	TArray<UBaseNode*> Children;

	UPROPERTY(VisibleAnywhere)
	int CurrentChild = 0;

	virtual ENodeStatus Update() override;
};
