// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectorNode.h"

ENodeStatus USelectorNode::Update()
{
    int childCount = Children.Num();

    for (; CurrentChild < childCount; CurrentChild++)
    {
        ENodeStatus result = Children[CurrentChild]->Process();
        switch (result)
        {
        case ENodeStatus::Success: return ENodeStatus::Success;
        case ENodeStatus::Failed: continue;
        case ENodeStatus::Running: return ENodeStatus::Running;
        }
    }

    Reset();
    return ENodeStatus::Failed;
}

void USelectorNode::OnEnter()
{
    CurrentChild = 0;
}

void USelectorNode::OnExit()
{
    CurrentChild = 0;
}
