// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGun.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseGun::ABaseGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

bool ABaseGun::SetupBlackboard(
	UBlackboardComponent* BlackboardComponent,
	USceneComponent* Muzzle,
	AActor* Shooter,
	USceneComponent* Head)
{
	if (IsValid(BlackboardComponent))
	{
		Blackboard = BlackboardComponent;
		Blackboard->SetValueAsObject(FName("SelfWeapon"), this);
		Blackboard->SetValueAsObject(FName("Muzzle"), Muzzle);
		Blackboard->SetValueAsObject(FName("Shooter"), Shooter);
		Blackboard->SetValueAsObject(FName("Head"), Head);

		// Setting ModificationAppliers for Stat Upgrades
		InstantiateModificationApplier(FName("BulletSpread"), &BulletSpreadMod);
		InstantiateModificationApplier(FName("BulletDamage"), &BulletDamageMod);
		InstantiateModificationApplier(FName("ProjectileSpeed"), &ProjectileSpeedMod);
		InstantiateModificationApplier(FName("BulletsPerShot"), &BulletsPerShotMod);
		InstantiateModificationApplier(FName("FireRate"), &FireRateMod);

		// Setting Delegates for Blackboard Callbacks
		OnBulletFired = NewObject<UDelegateContainerVecVec>();
		Blackboard->SetValueAsObject(FName("OnBulletFired"), OnBulletFired);

		OnBulletHit = NewObject<UDelegateContainerActorVec>();
		Blackboard->SetValueAsObject(FName("OnBulletHit"), OnBulletHit);

		// Setup the Blackboard for the nodes in the corresponding trees
		if (NodeTreeOnPressed != nullptr)
		{
			NodeTreeOnPressed->SetupBlackboard(BlackboardComponent);
		}

		if (NodeTreeOnHeld != nullptr)
		{
			NodeTreeOnHeld->SetupBlackboard(BlackboardComponent);
		}

		if (NodeTreeOnRelease != nullptr)
		{
			NodeTreeOnRelease->SetupBlackboard(BlackboardComponent);
		}

		IsBlackboardSet = true;
		return true;
	}

	return false;
}

void ABaseGun::InstantiateModificationApplier(const FName& KeyName, UModificationApplier** ModificationApplier) const
{
	// Checking if key exists in Blackboard
	if ((uint16)Blackboard->GetKeyID(KeyName) != MAX_uint16)
	{
		*ModificationApplier = NewObject<UModificationApplier>();
		Blackboard->SetValueAsObject(KeyName, *ModificationApplier);
	}
}

void ABaseGun::TraverseNodeTree(UBaseNode* NodeTree) const
{
	if (NodeTree == nullptr) return;

	float GameTime = UGameplayStatics::GetTimeSeconds(GetWorld());

	Blackboard->SetValueAsFloat(FName("GameTime"), GameTime);

	USceneComponent* Muzzle = Cast<USceneComponent>(Blackboard->GetValueAsObject(FName("Muzzle")));
	if (Muzzle)
	{
		Blackboard->SetValueAsVector(FName("MuzzleLocation"), Muzzle->GetComponentLocation());
		Blackboard->SetValueAsVector(FName("MuzzleDirection"), Muzzle->GetForwardVector());
	}

	USceneComponent* Head = Cast<USceneComponent>(Blackboard->GetValueAsObject(FName("Head")));
	if (Head)
	{
		Blackboard->SetValueAsVector(FName("HeadLocation"), Head->GetComponentLocation());
		Blackboard->SetValueAsVector(FName("HeadDirection"), Head->GetForwardVector());
	}

	if (NodeTree->Process() == ENodeStatus::Success)
	{
		OnGunFired.Broadcast(
			Blackboard->GetValueAsVector(FName("ShootLocation")),
			Blackboard->GetValueAsVector(FName("ShootDirection"))
		);
	}
}

void ABaseGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!TriggerHeld || !IsBlackboardSet) return;

	TraverseNodeTree(NodeTreeOnHeld);
}

void ABaseGun::ApplyUpgrade_Implementation(UUpgrade* Upgrade)
{
	Upgrade->TransferModifiers(Blackboard);
	Upgrades.Add(Upgrade);
}

TSubclassOf<UUserWidget> ABaseGun::GetCrosshair_Implementation() const
{
	return Crosshair;
}

void ABaseGun::StartAttacking_Implementation()
{
	TimeStarted = UGameplayStatics::GetTimeSeconds(GetWorld());
	Blackboard->SetValueAsFloat(FName("StartTimeTriggerPressed"), TimeStarted);

	TriggerHeld = true;
	OnFireHeld.Broadcast();

	TraverseNodeTree(NodeTreeOnPressed);
}

void ABaseGun::StopAttacking_Implementation()
{
	TriggerHeld = false;
	OnFireReleased.Broadcast();

	TraverseNodeTree(NodeTreeOnRelease);
}