// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTNodes/BaseNode.h"
//#include "Runtime/AIModule/Classes/AIController.h"
#include "GameFramework/Actor.h"
#include "GunTestActor.generated.h"

class UBlackboardComponent;
class UBlackboardData;

UCLASS()
class SPARKLEBLASTWEAPONS_API AGunTestActor : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AGunTestActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadWrite)
	UBlackboardComponent* Blackboard;

	//UPROPERTY(BlueprintReadOnly, EditAnywhere)
	//UBlackboardData* BlackboardData;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Instanced)
	UBaseNode* NodeTree;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	bool SetupBlackboard(UBlackboardComponent* BlackboardComponent);
};
