// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "../BTNodes/BaseNode.h"
#include "../Upgrades/Upgrade.h"
#include "../Upgrades/ModificationApplier.h"
#include "../DelegateContainers/DelegateContainerNone.h"
#include "../DelegateContainers/DelegateContainerVecVec.h"
#include "../DelegateContainers/DelegateContainerActorVec.h"
#include "FMODEvent.h"
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
	// When fire button gets pressed
	UPROPERTY(BlueprintAssignable)
	FOnDelegateMultiNone OnFireHeld;

	// When fire button gets released
	UPROPERTY(BlueprintAssignable)
	FOnDelegateMultiNone OnFireReleased;

	// When gun fires bullets
	UPROPERTY(BlueprintAssignable)
	FOnDelegateMultiVecVec OnGunFired;

	// When a projectile or a hitscan gets fired (can invoke multiple times if repeating)
	UPROPERTY(BlueprintReadOnly)
	UDelegateContainerVecVec* OnBulletFired;

	// When a hitscan hits a target (gets invoked per target)
	UPROPERTY(BlueprintReadOnly)
	UDelegateContainerActorVec* OnBulletHit;

	// Sets default values for this actor's properties
	ABaseGun();

	virtual void Tick(const float DeltaTime) override;

	// Transfers the upgrade modifiers to the blackboard and adds upgrade to the upgrades array
	UFUNCTION(BlueprintCallable)
	virtual void ApplyUpgrade_Implementation(UUpgrade* Upgrade) override;

	// Returns crosshair of gun
	UFUNCTION(BlueprintCallable)
	virtual TSubclassOf<UUserWidget> GetCrosshair_Implementation() const override;

	// Sets TriggerHeld to true, invokes InFireHeld, and starts traversing NodeTreeOnPressed
	UFUNCTION(BlueprintCallable)
	virtual void StartAttacking_Implementation() override;

	// Sets TriggerHeld to false, invokes InFireReleased, and starts traversing NodeTreeOnRelease
	UFUNCTION(BlueprintCallable)
	virtual void StopAttacking_Implementation() override;

protected:
	UPROPERTY(BlueprintReadWrite)
	UBlackboardComponent* Blackboard;

	// Behaviour Trees/Node Trees
	// Gets traversed when fire button is pressed
	UPROPERTY(Category = "Gun Properties", BlueprintReadOnly, EditAnywhere, Instanced)
	UBaseNode* NodeTreeOnPressed;

	// Gets traversed when fire button is held
	UPROPERTY(Category = "Gun Properties", BlueprintReadOnly, EditAnywhere, Instanced)
	UBaseNode* NodeTreeOnHeld;

	// Gets traversed when fire button is released
	UPROPERTY(Category = "Gun Properties", BlueprintReadOnly, EditAnywhere, Instanced)
	UBaseNode* NodeTreeOnRelease;

	// Crosshair widget that gets shown when gun is equipped
	UPROPERTY(Category = "Gun Properties", BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UUserWidget> Crosshair;

	// Shoot FMOD event that get plays when gun fires
	UPROPERTY(Category = "Gun Properties", BlueprintReadOnly, EditAnywhere)
	UFMODEvent* ShootFMODEvent;

	// Camera shake that occurs when gun fires
	UPROPERTY(Category = "Gun Properties", BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UCameraShakeBase> CameraShake;
	
	// Upgrades
	UPROPERTY()
	TArray<UUpgrade*> Upgrades;

	/*
	Stat Modifications
	Initially null pointers, but actual objects will be added using InstantiateModificationApplier
	ModificationAppliers are put into the blackboard for easier accessibility
	*/
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

	UFUNCTION(BlueprintCallable)
	bool SetupBlackboard(
		UBlackboardComponent* BlackboardComponent,
		USceneComponent* Muzzle,
		AActor* Shooter,
		USceneComponent* Head);

	/*
	Not a UFUNCTION, because double pointer would otherwise not be possible
	It is a double pointer so the pointer of the given ModificationApplier
	can be replaced with the pointer of a new ModificationApplier
	*/
	void InstantiateModificationApplier(const FName& KeyName, UModificationApplier** ModificationApplier) const;

private:
	UPROPERTY()
	float TimeStarted = 0.0f;

	UFUNCTION()
	void TraverseNodeTree(UBaseNode* NodeTree) const;
};
