// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

UCLASS( BlueprintType, abstract)
class SPARKLEBLASTWEAPONS_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Constructor(float AttackDamage, float Speed, bool Piercing, AActor* Shooter);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
