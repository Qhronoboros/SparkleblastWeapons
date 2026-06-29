// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

UCLASS( BlueprintType, abstract)
class SPARKLEBLASTWEAPONS_API ABaseProjectile : public AActor, public IProjectile
{
	GENERATED_BODY()
};
