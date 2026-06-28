// Fill out your copyright notice in the Description page of Project Settings.


#include "CooldownNode.h"
#include "BehaviorTree/BlackboardComponent.h"

void UCooldownNode::Reset()
{
	TimeStarted = -INFINITY;
	Child->Reset();
}

ENodeStatus UCooldownNode::Update()
{
	float GameTime = Blackboard->GetValueAsFloat(FName("GameTime"));

	// CooldownCurve calculates FireRate, while DefaultDuration is just in seconds
	// Frequency is how often the child gets processed per second
	float ActualFrequency = !CooldownCurve ? 1.0f / DefaultDuration :
		FMath::Max(CooldownCurve->
		GetFloatValue(GameTime - Blackboard->GetValueAsFloat(FName("StartTimeTriggerPressed"))), 0.0f);

	// Modify Frequency
	UModificationApplier* FrequencyMod = Cast<UModificationApplier>(Blackboard->GetValueAsObject(FrequencyBlackboardKey));
	if (FrequencyMod)
	{
		ActualFrequency = FrequencyMod->ApplyMod(ActualFrequency);
	}
	ActualFrequency = FMath::Max(ActualFrequency, 0.0f);

	float Duration = 1.0f / ActualFrequency;
	if (GameTime - TimeStarted >= Duration)
	{
		TimeStarted = GameTime;
		return Child->Process();
	}
	
	return ENodeStatus::Running;
}