// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	TSubclassOf<UUserWidget> GetCrosshair();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StartAttacking(USceneComponent* OwnerLook, AActor* OwnerShooter);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StopAttacking();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Attack(FTransform OwnerLookTransform);
};
