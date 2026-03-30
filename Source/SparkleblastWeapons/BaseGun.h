// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.h"
#include "BaseGun.generated.h"

UCLASS()
class SPARKLEBLASTWEAPONS_API ABaseGun : public AActor, public IWeapon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	TSubclassOf<UUserWidget> GetCrosshair_Implementation();

	UFUNCTION(BlueprintCallable)
	void StartAttacking_Implementation(USceneComponent* OwnerLook, AActor* OwnerShooter);

	UFUNCTION(BlueprintCallable)
	void StopAttacking_Implementation();

	UFUNCTION(BlueprintCallable)
	void Attack_Implementation(FTransform OwnerLookTransform);
};
