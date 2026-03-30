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
    virtual NodeStatus Update() override;

    virtual void OnEnter() override;
    virtual void OnExit() override;
};
