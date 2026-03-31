// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletTransformCalcMuzzleNode.h"
#include "BehaviorTree/BlackboardComponent.h"

NodeStatus UBulletTransformCalcMuzzleNode::Update()
{
	Blackboard->SetValueAsVector(FName("ShootLocation"), 
		Blackboard->GetValueAsVector("MuzzleLocation"));

	float Spread = Blackboard->GetValueAsFloat(FName("BulletSpread"));

	// Degrees to Radian
	FVector RandomizedDirection = FMath::VRandCone(
		Blackboard->GetValueAsVector("MuzzleDirection"),
		PI / 180.0f * Spread);

	Blackboard->SetValueAsVector(FName("ShootDirection"), RandomizedDirection);

	return NodeStatus::Success;
}