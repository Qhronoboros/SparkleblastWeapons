// Fill out your copyright notice in the Description page of Project Settings.


#include "GunTestActor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGunTestActor::AGunTestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGunTestActor::BeginPlay()
{
	Super::BeginPlay();
}

bool AGunTestActor::SetupBlackboard(UBlackboardComponent* BlackboardComponent, AActor* Shooter)
{
	if (IsValid(BlackboardComponent))
	{
		Blackboard = BlackboardComponent;
		Blackboard->SetValueAsObject(FName("SelfWeapon"), this);
		Blackboard->SetValueAsObject(FName("Shooter"), Shooter);

		OnBulletFired = NewObject<UDelegateContainerVecVec>();
		Blackboard->SetValueAsObject(FName("OnBulletFired"), OnBulletFired);

		OnBulletHit = NewObject<UDelegateContainerActorVec>();
		Blackboard->SetValueAsObject(FName("OnBulletHit"), OnBulletHit);

		NodeTree->SetupBlackboard(BlackboardComponent);
		IsBlackboardSet = true;
		return true;
	}

	return false;
}

void AGunTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!TriggerHeld || !IsBlackboardSet) return;

	float GameTime = UGameplayStatics::GetTimeSeconds(GetWorld());

	Blackboard->SetValueAsFloat(FName("GameTime"), GameTime);

	Blackboard->SetValueAsVector(FName("MuzzleLocation"), GetActorLocation());
	Blackboard->SetValueAsVector(FName("MuzzleDirection"), GetActorForwardVector());

	Blackboard->SetValueAsFloat(FName("Cooldown"), 1.0f /
			FMath::Max(FireRateCurve->GetFloatValue(GameTime - TimeStarted), 0.0f));

	// Set HeadLocation, HeadDirection, MuzzleLocation, and MuzzleDirection

	if (NodeTree->Process() == NodeStatus::Success)
	{
		// OnGunFired
	}
}

TSubclassOf<UUserWidget> AGunTestActor::GetCrosshair()
{
	return TSubclassOf<UUserWidget>();
}

void AGunTestActor::StartAttacking(USceneComponent* OwnerLook, AActor* OwnerShooter)
{
	TimeStarted = UGameplayStatics::GetTimeSeconds(GetWorld());
	TriggerHeld = true;
}

void AGunTestActor::StopAttacking()
{
	TriggerHeld = false;
}

void AGunTestActor::Attack(FTransform OwnerLookTransform)
{

}

