// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseNode.h"

void UBaseNode::SetupBlackboard(UBlackboardComponent* NewBlackboard)
{
	Blackboard = NewBlackboard;
}

ENodeStatus UBaseNode::Process()
{
    if (!WasEntered)
    {
        OnEnter();
        WasEntered = true;
    }

    ENodeStatus result = Update();
    if (result != ENodeStatus::Running)
    {
        OnExit();
        WasEntered = false;
    }
    return result;
}