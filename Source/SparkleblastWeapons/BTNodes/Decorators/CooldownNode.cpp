// Fill out your copyright notice in the Description page of Project Settings.


#include "CooldownNode.h"
#include "BehaviorTree/BlackboardComponent.h"

void UCooldownNode::Reset()
{
	TimeStarted = -INFINITY;
	Child->Reset();
}

NodeStatus UCooldownNode::Update()
{
	float GameTime = Blackboard->GetValueAsFloat(FName("GameTime"));
	float ActualDuration = !CooldownCurve ? DefaultDuration : 
		1.0f / FMath::Max(CooldownCurve->
		GetFloatValue(GameTime - Blackboard->GetValueAsFloat(FName("StartTimeTriggerPressed"))), 0.0f);

	if (GameTime - TimeStarted >= ActualDuration)
	{
		TimeStarted = GameTime;
		return Child->Process();
	}
	
	return NodeStatus::Running;
}