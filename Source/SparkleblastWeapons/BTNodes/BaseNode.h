// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NodeStatus.h"
#include "Engine/DataAsset.h"
#include "BaseNode.generated.h"

class UBlackboardComponent;
class UBlackboardData;

// Not used by itself, but used for inheritance
UCLASS(EditInlineNew, BlueprintType, abstract)
class SPARKLEBLASTWEAPONS_API UBaseNode : public UDataAsset
{
	GENERATED_BODY()

public:
	// Set given blackboard for itself
	UFUNCTION(BlueprintCallable)
	virtual void SetupBlackboard(UBlackboardComponent* NewBlackboard);

	virtual void Reset() { };

	// Takes care of calling OnEnter, Update, and OnExit
	UFUNCTION(BlueprintCallable)
	virtual ENodeStatus Process();

protected:
	UBlackboardComponent* Blackboard;

	virtual ENodeStatus Update() PURE_VIRTUAL(UBaseNode::Update, return ENodeStatus::Success;);

	virtual void OnEnter() { };
	virtual void OnExit() { };

private:
	UPROPERTY()
	bool WasEntered = false;
};