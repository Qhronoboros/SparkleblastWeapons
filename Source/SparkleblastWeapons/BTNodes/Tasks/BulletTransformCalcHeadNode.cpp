// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletTransformCalcHeadNode.h"
#include "BehaviorTree/BlackboardComponent.h"

// Set ShootLocation and ShootDirection in Blackboard
// ShootLocation = HeadLocation
// ShootDirection = HeadDirection
ENodeStatus UBulletTransformCalcHeadNode::Update()
{
	Blackboard->SetValueAsVector(FName("ShootLocation"),
		Blackboard->GetValueAsVector("HeadLocation"));

	// Apply BulletSpread, also convert Degrees to Radian
	FVector RandomizedDirection = FMath::VRandCone(
		Blackboard->GetValueAsVector("HeadDirection"),
		PI / 180.0f * BulletSpread);

	Blackboard->SetValueAsVector(FName("ShootDirection"), RandomizedDirection);

	return ENodeStatus::Success;
}