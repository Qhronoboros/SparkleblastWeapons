// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletTransformCalcAccurateNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

NodeStatus UBulletTransformCalcAccurateNode::Update()
{
	UWorld* World = Blackboard->GetValueAsObject(FName("SelfWeapon"))->GetWorld();
	float MaxDistance = Blackboard->GetValueAsFloat(FName("MaxShootDistance"));
	FVector HeadLocation = Blackboard->GetValueAsVector(FName("HeadLocation"));
	FVector HeadDirection = Blackboard->GetValueAsVector(FName("HeadDirection"));
	FVector MuzzleLocation = Blackboard->GetValueAsVector(FName("MuzzleLocation"));

	// Degrees to Radian
	FVector RandomizedDirection = FMath::VRandCone(HeadDirection, PI/180.0f * BulletSpread);

	// Default
	FVector OutDirection;

	FHitResult Hit;
	if (!GetLineTraceHit(World, HeadLocation, RandomizedDirection, MaxDistance, Hit))
	{
		UE_LOG(LogTemp, Warning, TEXT("(UBulletTransformCalcAccurateNode) Did not hit any solid object with lineTrace"));

		// If not hitting anything, get the point with the maximum distance
		OutDirection = RandomizedDirection * MaxDistance + HeadLocation - MuzzleLocation;
	}
	else
	{
		OutDirection = Hit.Location - MuzzleLocation;
	}

	OutDirection.Normalize();

	Blackboard->SetValueAsVector(FName("ShootLocation"), MuzzleLocation);

	Blackboard->SetValueAsVector(FName("ShootDirection"), OutDirection);

	return NodeStatus::Success;
}

bool UBulletTransformCalcAccurateNode::GetLineTraceHit(UWorld* World, FVector Location, FVector Direction, float MaxDistance, FHitResult& Hit)
{
	FCollisionQueryParams CollisionParams;
	if (!World->LineTraceSingleByChannel(Hit, Location, Location + Direction * MaxDistance, ECC_Visibility, CollisionParams)) return false;

	return true;
}
