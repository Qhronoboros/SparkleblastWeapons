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

	// Modify Spread
	float ActualBulletSpread = BulletSpread;
	UModificationApplier* BulletSpreadMod = Cast<UModificationApplier>(Blackboard->GetValueAsObject(BulletSpreadBlackboardKey));
	if (BulletSpreadMod)
	{
		ActualBulletSpread = BulletSpreadMod->ApplyMod(ActualBulletSpread);
	}
	ActualBulletSpread = FMath::Max(ActualBulletSpread, 0.0f);

	// Apply BulletSpread, also convert Degrees to Radian
	FVector RandomizedDirection = FMath::VRandCone(
		Blackboard->GetValueAsVector("HeadDirection"),
		PI / 180.0f * ActualBulletSpread);

	Blackboard->SetValueAsVector(FName("ShootDirection"), RandomizedDirection);

	return ENodeStatus::Success;
}