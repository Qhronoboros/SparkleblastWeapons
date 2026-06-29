// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Upgrade.h"
#include "GameFramework/Actor.h"
#include "PickUp.generated.h"

UCLASS()
class SPARKLEBLASTWEAPONS_API APickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	UUpgrade* Upgrade;
};
