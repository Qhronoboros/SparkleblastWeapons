// Fill out your copyright notice in the Description page of Project Settings.

#include "DecoratorNode.h"

void UDecoratorNode::SetupBlackboard(UBlackboardComponent* NewBlackboard)
{
	Blackboard = NewBlackboard;
	Child->SetupBlackboard(NewBlackboard);
}

void UDecoratorNode::Reset()
{
	Child->Reset();
}

NodeStatus UDecoratorNode::Update()
{
	return Child->Process();
}