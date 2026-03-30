// Fill out your copyright notice in the Description page of Project Settings.


#include "CooldownNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void UCooldownNode::SetupBlackboard(UBlackboardComponent* NewBlackboard)
{
	Blackboard = NewBlackboard;
	Child->SetupBlackboard(NewBlackboard);
}

void UCooldownNode::Reset()
{
	TimeStarted = 0.0f;
	Child->Reset();
}

NodeStatus UCooldownNode::Update()
{
	float GameTime = Blackboard->GetValueAsFloat(FName("GameTime"));
	if (GameTime - TimeStarted >= Duration)
	{
		TimeStarted = GameTime;
		return Child->Process();
	}

	return NodeStatus::Running;
}