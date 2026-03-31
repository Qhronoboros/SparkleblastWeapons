// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletTransformCalcHeadNode.h"
#include "BehaviorTree/BlackboardComponent.h"

NodeStatus UBulletTransformCalcHeadNode::Update()
{
	Blackboard->SetValueAsVector(FName("ShootLocation"),
		Blackboard->GetValueAsVector("HeadLocation"));

	float Spread = Blackboard->GetValueAsFloat(FName("BulletSpread"));

	// Degrees to Radian
	FVector RandomizedDirection = FMath::VRandCone(
		Blackboard->GetValueAsVector("HeadDirection"),
		PI / 180.0f * Spread);

	Blackboard->SetValueAsVector(FName("ShootDirection"), RandomizedDirection);

	return NodeStatus::Success;
}