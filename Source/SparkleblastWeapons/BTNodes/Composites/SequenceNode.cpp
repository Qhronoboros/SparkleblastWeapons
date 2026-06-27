// Fill out your copyright notice in the Description page of Project Settings.


#include "SequenceNode.h"

ENodeStatus USequenceNode::Update()
{
    int childCount = Children.Num();

    for (; CurrentChild < childCount; CurrentChild++)
    {
        ENodeStatus result = Children[CurrentChild]->Process();
        switch (result)
        {
        case ENodeStatus::Success: continue;
        case ENodeStatus::Failed: return ENodeStatus::Failed;
        case ENodeStatus::Running: return ENodeStatus::Running;
        }
    }

    Reset();
    return ENodeStatus::Success;
}

void USequenceNode::OnEnter()
{
    CurrentChild = 0;
}

void USequenceNode::OnExit()
{
    CurrentChild = 0;
}