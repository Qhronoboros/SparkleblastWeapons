// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootProjectile.h"
#include "BehaviorTree/BlackboardComponent.h"

NodeStatus UShootProjectile::Update()
{
	if (!Projectile)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: Provided Projectile is null"), *FString(UTF8_TO_TCHAR(__FUNCTION__)));
		return NodeStatus::Failed;
	}

	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	UWorld* World = Blackboard->GetValueAsObject(FName("SelfActor"))->GetWorld();
	FVector StartLocation = Blackboard->GetValueAsVector(FName("ShootLocation"));
	FVector Direction = Blackboard->GetValueAsVector(FName("ShootDirection"));
	
	ABaseProjectile* SpawnedProjectile = World->SpawnActor<ABaseProjectile>(Projectile, StartLocation, Direction.Rotation(), spawnParams);

	AActor* actor = Cast<AActor>(Blackboard->GetValueAsObject(FName("SelfActor")));

	if (!actor)
	{
		return NodeStatus::Failed;
	}

	float Damage = Blackboard->GetValueAsFloat(FName("BulletDamage"));
	float Speed = Blackboard->GetValueAsFloat(FName("ProjectileSpeed"));
	bool Piercing = Blackboard->GetValueAsBool(FName("Piercing"));

	SpawnedProjectile->Constructor(Damage, Speed, Piercing, actor);
	return NodeStatus::Success;
}