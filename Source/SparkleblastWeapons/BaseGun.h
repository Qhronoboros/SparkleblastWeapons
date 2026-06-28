// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTNodes/BaseNode.h"
#include "Weapon.h"
#include "Upgrade.h"
#include "FMODEvent.h"
#include "DelegateContainers/DelegateContainerNone.h"
#include "DelegateContainers/DelegateContainerVecVec.h"
#include "DelegateContainers/DelegateContainerActorVec.h"
#include "ModificationApplier.h"
#include "GameFramework/Actor.h"
#include "BaseGun.generated.h"

class UBlackboardComponent;
class UBlackboardData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDelegateMultiNone);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDelegateMultiVecVec, FVector, Vec1, FVector, Vec2);

UCLASS()
class SPARKLEBLASTWEAPONS_API ABaseGun : public AActor, public IWeapon
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
	ABaseGun();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void ApplyUpgrade_Implementation(UUpgrade* Upgrade) override;

	UFUNCTION(BlueprintCallable)
	virtual TSubclassOf<UUserWidget> GetCrosshair_Implementation() override;

	UFUNCTION(BlueprintCallable)
	virtual void StartAttacking_Implementation() override;

	UFUNCTION(BlueprintCallable)
	virtual void StopAttacking_Implementation() override;

protected:
	UPROPERTY(BlueprintReadWrite)
	UBlackboardComponent* Blackboard;

	UPROPERTY(Category = "Gun Properties", BlueprintReadOnly, EditAnywhere, Instanced)
	UBaseNode* NodeTreeOnPressed;

	UPROPERTY(Category = "Gun Properties", BlueprintReadOnly, EditAnywhere, Instanced)
	UBaseNode* NodeTreeOnHeld;

	UPROPERTY(Category = "Gun Properties", BlueprintReadOnly, EditAnywhere, Instanced)
	UBaseNode* NodeTreeOnRelease;

	UPROPERTY(Category = "Gun Properties", BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UUserWidget> Crosshair;

	UPROPERTY(Category = "Gun Properties", BlueprintReadOnly, EditAnywhere)
	UFMODEvent* ShootFMODEvent;

	UPROPERTY(Category = "Gun Properties", BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UCameraShakeBase> CameraShake;
	
	// Upgrades
	UPROPERTY()
	TArray<UUpgrade*> Upgrades;

	// Stat Modifications
	UPROPERTY()
	UModificationApplier* BulletSpreadMod;

	UPROPERTY()
	UModificationApplier* BulletDamageMod;

	UPROPERTY()
	UModificationApplier* ProjectileSpeedMod;

	UPROPERTY()
	UModificationApplier* BulletsPerShotMod;

	UPROPERTY()
	UModificationApplier* FireRateMod;

	UPROPERTY()
	bool IsBlackboardSet = false;
	
	UPROPERTY()
	bool TriggerHeld = false;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	bool SetupBlackboard(
		UBlackboardComponent* BlackboardComponent,
		USceneComponent* Muzzle,
		AActor* Shooter,
		USceneComponent* Head);

	// Not UFUNCTION, because double pointer would not be possible
	void InstantiateModificationApplier(const FName& KeyName, UModificationApplier** ModificationApplier);

private:
	UPROPERTY()
	float TimeStarted = 0.0f;

	UFUNCTION()
	void TraverseNodeTree(UBaseNode* NodeTree);
};
