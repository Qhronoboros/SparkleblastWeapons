// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseNode.h"
#include "DecoratorNode.generated.h"

UCLASS()
class SPARKLEBLASTWEAPONS_API UDecoratorNode : public UBaseNode
{
	GENERATED_BODY()

public:
	virtual void SetupBlackboard(UBlackboardComponent* NewBlackboard) override;
	virtual void Reset() override;

protected:
	UPROPERTY(EditAnywhere, Instanced)
	UBaseNode* Child;

	virtual NodeStatus Update() override;
};
