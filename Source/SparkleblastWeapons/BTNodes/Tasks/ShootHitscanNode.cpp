// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootHitscanNode.h"
#include "../../Health.h"
#include "../../DelegateContainers/DelegateContainerVecVec.h"
#include "../../DelegateContainers/DelegateContainerActorVec.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"

NodeStatus UShootHitscanNode::Update()
{
	// Multi Line Trace Hitscan
	UWorld* World = Blackboard->GetValueAsObject(FName("SelfWeapon"))->GetWorld();
	FVector StartLocation = Blackboard->GetValueAsVector(FName("ShootLocation"));
	FVector Direction = Blackboard->GetValueAsVector(FName("ShootDirection"));

	float MaxDistance = Blackboard->GetValueAsFloat(FName("MaxShootDistance"));

	bool Piercing = Blackboard->GetValueAsBool(FName("Piercing"));

	TArray<FHitResult> HitResults;
	LineTraceHitscan(
		World,
		StartLocation,
		Direction,
		MaxDistance,
		HitResults,
		Piercing);

	// Loop through results

	FVector LatestImpactPoint = StartLocation + Direction * MaxDistance;
	for (FHitResult Hit : HitResults)
	{
		AActor* HitActor = Hit.GetActor();
		// Check if hit Actor is valid
		if (!HitActor) continue;

		// Set Latest Impact Point
		LatestImpactPoint = Hit.ImpactPoint;

		// Deal Damage
		AActor* actor = Cast<AActor>(Blackboard->GetValueAsObject(FName("Shooter")));
		UHealth* HealthComponent = HitActor->GetComponentByClass<UHealth>();
		if (HealthComponent)
		{
			HealthComponent->DealDamage(actor, Damage);
		}

		// Callbacks
		UDelegateContainerVecVec* BulletFired = Cast<UDelegateContainerVecVec>(Blackboard->GetValueAsObject(FName("OnBulletFired")));
		if (BulletFired)
		{
			BulletFired->ExecuteDelegates(StartLocation, Direction);
		}

		UDelegateContainerActorVec* BulletHit = Cast<UDelegateContainerActorVec>(Blackboard->GetValueAsObject(FName("OnBulletHit")));
		if (BulletHit)
		{
			BulletHit->ExecuteDelegates(actor, LatestImpactPoint);
		}
		
		if (PrintHitscan)
		{
			FString text = "Hitscan: " + UKismetSystemLibrary::GetDisplayName(HitActor);
			UE_LOG(LogTemp, Display, TEXT("%s"), *text);

			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("%s"), *text));
			}
		}
	}
	// End of loop, If Show Debug Line, Draw Debug Line
	if (ShowDebugLine)
	{
		DrawDebugLine(World, StartLocation, LatestImpactPoint, FColor::Blue, false, DebugLineDuration);
	}

	return NodeStatus::Success;
}

bool UShootHitscanNode::LineTraceHitscan(
	const UWorld* World,
	const FVector StartLocation,
	const FVector Direction,
	const float MaxDistance,
	TArray<FHitResult>& Hits,
	const bool Piercing)
{
	FCollisionQueryParams CollisionParams;

	if (Piercing)
	{
		if (!World->LineTraceMultiByChannel(Hits, StartLocation, StartLocation + Direction * MaxDistance, ECC_Visibility, CollisionParams))
		{
			UE_LOG(LogTemp, Warning, TEXT("%s: Did not hit any object with MultiLineTrace"), *FString(UTF8_TO_TCHAR(__FUNCTION__)));
			return false;
		}
	}
	else
	{
		FHitResult Hit;
		if (!World->LineTraceSingleByChannel(Hit, StartLocation, StartLocation + Direction * MaxDistance, ECC_Visibility, CollisionParams))
		{
			UE_LOG(LogTemp, Warning, TEXT("%s: Did not hit any object with SingleLineTrace"), *FString(UTF8_TO_TCHAR(__FUNCTION__)));
			return false;
		}

		Hits.Add(Hit);
	}
	return true;
}