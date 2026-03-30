// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseNode.h"

void UBaseNode::SetupBlackboard(UBlackboardComponent* NewBlackboard)
{
	Blackboard = NewBlackboard;
}

NodeStatus UBaseNode::Process()
{
    if (!WasEntered)
    {
        OnEnter();
        WasEntered = true;
    }

    NodeStatus result = Update();
    if (result != NodeStatus::Running)
    {
        OnExit();
        WasEntered = false;
    }
    return result;
}