// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CompositeNode.h"
#include "SequenceNode.generated.h"

/**
 * 
 */
UCLASS()
class SPARKLEBLASTWEAPONS_API USequenceNode : public UCompositeNode
{
	GENERATED_BODY()

protected:
    /*
    Process through all children until one fails or is still running
    and returns the corresponding status.
    Starts with the last processed child unless reset
    Returns the Success status if all children succeed
    */
    virtual ENodeStatus Update() override;

    // Reset currentChild to 0
    virtual void OnEnter() override;
    // Reset currentChild to 0
    virtual void OnExit() override;
};
