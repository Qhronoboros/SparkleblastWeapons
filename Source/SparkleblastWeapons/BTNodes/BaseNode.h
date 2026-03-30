// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NodeStatus.h"
#include "Engine/DataAsset.h"
#include "BaseNode.generated.h"

class UBlackboardComponent;
class UBlackboardData;

UCLASS( EditInlineNew, BlueprintType, abstract )
class SPARKLEBLASTWEAPONS_API UBaseNode : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void SetupBlackboard(UBlackboardComponent* NewBlackboard);

	virtual void Reset() { };

	UFUNCTION(BlueprintCallable)
	virtual NodeStatus Process();

protected:
	UBlackboardComponent* Blackboard;

	virtual NodeStatus Update() PURE_VIRTUAL(UBaseNode::Update, return NodeStatus::Success;);

	virtual void OnEnter() { };
	virtual void OnExit() { };

private:
	bool WasEntered = false;
};