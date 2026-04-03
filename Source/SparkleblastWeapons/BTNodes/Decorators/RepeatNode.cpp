// Fill out your copyright notice in the Description page of Project Settings.


#include "RepeatNode.h"
#include "BehaviorTree/BlackboardComponent.h"

NodeStatus URepeatNode::Update()
{
	//int ActualRepeat = RepeatBlackboardKey == "" ?
	//	DefaultRepeat : Blackboard->GetValueAsInt(FName(RepeatBlackboardKey));

	int ActualRepeat = RepeatAmount;

	for (int i = 0; i < ActualRepeat; i++)
	{
		if (Child->Process() != NodeStatus::Success) break;
	}

	return NodeStatus::Success;
}