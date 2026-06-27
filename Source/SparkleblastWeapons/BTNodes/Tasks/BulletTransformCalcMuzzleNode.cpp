// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletTransformCalcMuzzleNode.h"
#include "BehaviorTree/BlackboardComponent.h"

// Set ShootLocation and ShootDirection in Blackboard
// ShootLocation = MuzzleLocation
// ShootDirection = MuzzleDirection
ENodeStatus UBulletTransformCalcMuzzleNode::Update()
{
	Blackboard->SetValueAsVector(FName("ShootLocation"), 
		Blackboard->GetValueAsVector("MuzzleLocation"));

	// Apply BulletSpread, also convert Degrees to Radian
	FVector RandomizedDirection = FMath::VRandCone(
		Blackboard->GetValueAsVector("MuzzleDirection"),
		PI / 180.0f * BulletSpread);

	Blackboard->SetValueAsVector(FName("ShootDirection"), RandomizedDirection);

	return ENodeStatus::Success;
}