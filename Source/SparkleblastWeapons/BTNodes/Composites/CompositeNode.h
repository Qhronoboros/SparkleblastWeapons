// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseNode.h"
#include "CompositeNode.generated.h"

UCLASS()
class SPARKLEBLASTWEAPONS_API UCompositeNode : public UBaseNode
{
	GENERATED_BODY()

public:	
	virtual void SetupBlackboard(UBlackboardComponent* NewBlackboard) override;

    virtual void Reset() override;

protected:
	UPROPERTY(EditAnywhere, Instanced)
	TArray<UBaseNode*> Children;

	UPROPERTY(VisibleAnywhere)
	int CurrentChild = 0;

	virtual NodeStatus Update() override;
};
