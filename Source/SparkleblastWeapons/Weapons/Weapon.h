// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Upgrades/Upgrade.h"
#include "UObject/Interface.h"
#include "Blueprint/UserWidget.h"
#include "Weapon.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UWeapon : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SPARKLEBLASTWEAPONS_API IWeapon
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void InitializeWeapon(AActor* Shooter, USceneComponent* Head);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ApplyUpgrade(UUpgrade* Upgrade);
	virtual void ApplyUpgrade_Implementation(UUpgrade* Upgrade) { };

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	TSubclassOf<UUserWidget> GetCrosshair();
	virtual TSubclassOf<UUserWidget> GetCrosshair_Implementation() { return NULL; };

	// When Attack button held
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartAttacking();
	virtual void StartAttacking_Implementation() { };

	// When Attack button released
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StopAttacking();
	virtual void StopAttacking_Implementation() { };
};
