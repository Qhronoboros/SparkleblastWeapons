// Fill out your copyright notice in the Description page of Project Settings.

#include "CompositeNode.h"

void UCompositeNode::SetupBlackboard(UBlackboardComponent* NewBlackboard)
{
    Blackboard = NewBlackboard;

    for (UBaseNode* Child : Children)
    {
        if (Child)
        {
            Child->SetupBlackboard(NewBlackboard);
        }
        else
        {
            UE_LOG(LogTemp, Display, TEXT("Child is NULL in Composite"));
        }
    }
}

void UCompositeNode::Reset()
{
    CurrentChild = 0;
    for (UBaseNode* Child : Children)
    {
        Child->Reset();
    }
}

NodeStatus UCompositeNode::Update()
{
    return Children[CurrentChild]->Process();
}