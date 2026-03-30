// Fill out your copyright notice in the Description page of Project Settings.


#include "SequenceNode.h"

NodeStatus USequenceNode::Update()
{
    int childCount = Children.Num();

    for (; CurrentChild < childCount; CurrentChild++)
    {
        NodeStatus result = Children[CurrentChild]->Process();
        switch (result)
        {
        case NodeStatus::Success: continue;
        case NodeStatus::Failed: return NodeStatus::Failed;
        case NodeStatus::Running: return NodeStatus::Running;
        }
    }

    Reset();
    return NodeStatus::Success;
}

void USequenceNode::OnEnter()
{
    CurrentChild = 0;
}

void USequenceNode::OnExit()
{
    CurrentChild = 0;
}