// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseNode.h"
#include "../../BaseProjectile.h"
#include "ShootProjectile.generated.h"

/**
 * 
 */
UCLASS()
class SPARKLEBLASTWEAPONS_API UShootProjectile : public UBaseNode
{
	GENERATED_BODY()

protected:
	virtual NodeStatus Update() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseProjectile> Projectile;
};
