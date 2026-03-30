// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectorNode.h"

NodeStatus USelectorNode::Update()
{
    int childCount = Children.Num();

    for (; CurrentChild < childCount; CurrentChild++)
    {
        NodeStatus result = Children[CurrentChild]->Process();
        switch (result)
        {
        case NodeStatus::Success: return NodeStatus::Success;
        case NodeStatus::Failed: continue;
        case NodeStatus::Running: return NodeStatus::Running;
        }
    }

    Reset();
    return NodeStatus::Failed;
}

void USelectorNode::OnEnter()
{
    CurrentChild = 0;
}

void USelectorNode::OnExit()
{
    CurrentChild = 0;
}
