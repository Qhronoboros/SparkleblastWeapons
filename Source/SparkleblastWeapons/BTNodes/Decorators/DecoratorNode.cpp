// Fill out your copyright notice in the Description page of Project Settings.

#include "DecoratorNode.h"

void UDecoratorNode::SetupBlackboard(UBlackboardComponent* NewBlackboard)
{
	Blackboard = NewBlackboard;

    if (Child)
    {
        Child->SetupBlackboard(NewBlackboard);
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT("Child is NULL in Decorator"));
    }
}

void UDecoratorNode::Reset()
{
	Child->Reset();
}

NodeStatus UDecoratorNode::Update()
{
	return Child->Process();
}