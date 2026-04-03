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

// Called when the game starts or when spawned
void ABaseGun::BeginPlay()
{
	Super::BeginPlay();
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

		OnBulletFired = NewObject<UDelegateContainerVecVec>();
		Blackboard->SetValueAsObject(FName("OnBulletFired"), OnBulletFired);

		OnBulletHit = NewObject<UDelegateContainerActorVec>();
		Blackboard->SetValueAsObject(FName("OnBulletHit"), OnBulletHit);

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

void ABaseGun::TraverseNodeTree(UBaseNode* NodeTree)
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

	if (NodeTree->Process() == NodeStatus::Success)
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

TSubclassOf<UUserWidget> ABaseGun::GetCrosshair_Implementation()
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