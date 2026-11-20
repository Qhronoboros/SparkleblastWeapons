// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseNode.h"
#include "../../Upgrades/ModificationApplier.h"
#include "BulletTransformCalcMuzzleNode.generated.h"

/**
 * 
 */
UCLASS()
class SPARKLEBLASTWEAPONS_API UBulletTransformCalcMuzzleNode : public UBaseNode
{
	GENERATED_BODY()

protected:
	/*
	// Set ShootLocation and ShootDirection in Blackboard
	// ShootLocation = MuzzleLocation
	// ShootDirection = MuzzleDirection
	*/
	virtual ENodeStatus Update() override;

private:
	// Blackboard key for Modification Applier
	UPROPERTY(EditAnywhere)
	FName BulletSpreadBlackboardKey = FName("BulletSpread");

	// Base size of bullet spread cone in radians
	UPROPERTY(EditAnywhere)
	float BulletSpread = 0.0f;
};
