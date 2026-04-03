// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootProjectile.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../DelegateContainers/DelegateContainerVecVec.h"

NodeStatus UShootProjectile::Update()
{
	if (!Projectile)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: Provided Projectile is null"), *FString(UTF8_TO_TCHAR(__FUNCTION__)));
		return NodeStatus::Failed;
	}

	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	UWorld* World = Blackboard->GetValueAsObject(FName("SelfWeapon"))->GetWorld();
	FVector StartLocation = Blackboard->GetValueAsVector(FName("ShootLocation"));
	FVector Direction = Blackboard->GetValueAsVector(FName("ShootDirection"));
	
	ABaseProjectile* SpawnedProjectile = World->SpawnActor<ABaseProjectile>(Projectile, StartLocation, Direction.Rotation(), spawnParams);

	AActor* Shooter = Cast<AActor>(Blackboard->GetValueAsObject(FName("Shooter")));

	if (!Shooter)
	{
		return NodeStatus::Failed;
	}

	//float Damage = Blackboard->GetValueAsFloat(FName("BulletDamage"));
	//float Speed = Blackboard->GetValueAsFloat(FName("ProjectileSpeed"));
	bool Piercing = Blackboard->GetValueAsBool(FName("Piercing"));

	SpawnedProjectile->Constructor(Damage, Speed, Piercing, Shooter);

	// Callback
	UDelegateContainerVecVec* BulletFired = Cast<UDelegateContainerVecVec>(Blackboard->GetValueAsObject(FName("OnBulletFired")));
	if (BulletFired)
	{
		BulletFired->ExecuteDelegates(StartLocation, Direction);
	}

	return NodeStatus::Success;
}