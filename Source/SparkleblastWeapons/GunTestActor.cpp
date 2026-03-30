// Fill out your copyright notice in the Description page of Project Settings.


#include "GunTestActor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

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

bool AGunTestActor::SetupBlackboard(UBlackboardComponent* BlackboardComponent)
{
	if (IsValid(BlackboardComponent))
	{
		Blackboard = BlackboardComponent;
		NodeTree->SetupBlackboard(BlackboardComponent);
		return true;
	}

	return false;
}

// Called every frame
void AGunTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

