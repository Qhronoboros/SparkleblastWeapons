// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTNodes/BaseNode.h"
//#include "Runtime/AIModule/Classes/AIController.h"
#include "Weapon.h"
#include "FMODEvent.h"
#include "DelegateContainers/DelegateContainerNone.h"
#include "DelegateContainers/DelegateContainerVecVec.h"
#include "DelegateContainers/DelegateContainerActorVec.h"
#include "GameFramework/Actor.h"
#include "GunTestActor.generated.h"

class UBlackboardComponent;
class UBlackboardData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDelegateMultiNone);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDelegateMultiVecVec, FVector, Vec1, FVector, Vec2);

UCLASS()
class SPARKLEBLASTWEAPONS_API AGunTestActor : public AActor
{
	GENERATED_BODY()
	
public:
	// Delegates
	UPROPERTY(BlueprintAssignable)
	FOnDelegateMultiNone OnFireHeld;
	
	UPROPERTY(BlueprintAssignable)
	FOnDelegateMultiNone OnFireReleased;

	UPROPERTY(BlueprintAssignable)
	FOnDelegateMultiVecVec OnGunFired;

	UPROPERTY(BlueprintReadOnly)
	UDelegateContainerVecVec* OnBulletFired;

	UPROPERTY(BlueprintReadOnly)
	UDelegateContainerActorVec* OnBulletHit;

	// Sets default values for this actor's properties
	AGunTestActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual TSubclassOf<UUserWidget> GetCrosshair();

	UFUNCTION(BlueprintCallable)
	virtual void StartAttacking(USceneComponent* OwnerLook, AActor* OwnerShooter);

	UFUNCTION(BlueprintCallable)
	virtual void StopAttacking();

	UFUNCTION(BlueprintCallable)
	virtual void Attack(FTransform OwnerLookTransform);

protected:
	UPROPERTY(BlueprintReadWrite)
	UBlackboardComponent* Blackboard;

	UPROPERTY(Category = "Gun Properties", BlueprintReadOnly, EditAnywhere, Instanced)
	UBaseNode* NodeTree;

	UPROPERTY(Category="Gun Properties", BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UUserWidget> Crosshair;

	UPROPERTY(Category = "Gun Properties", BlueprintReadOnly, EditAnywhere)
	UFMODEvent* ShootFMODEvent;

	UPROPERTY(Category = "Gun Properties", BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UCameraShakeBase> CameraShake;

	UPROPERTY(Category = "Gun Properties", BlueprintReadOnly, EditAnywhere)
	UCurveFloat* FireRateCurve;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	bool SetupBlackboard(UBlackboardComponent* BlackboardComponent, AActor* Shooter);

	bool IsBlackboardSet = false;
	bool TriggerHeld = false;

private:
	float TimeStarted = 0.0f;
};
