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
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets the member variables (in Blueprint)
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Constructor(float AttackDamage, float Speed, bool Piercing, AActor* Shooter);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
