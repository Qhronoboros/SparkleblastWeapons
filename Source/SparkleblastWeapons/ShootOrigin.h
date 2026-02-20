// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShootOrigin.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class SPARKLEBLASTWEAPONS_API UShootOrigin : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShootOrigin();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxDistance;

public:	
	UFUNCTION()
	bool GetLineTraceHit(FVector location, FVector direction, FHitResult& hit);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	void GetVectorsOwner(
		FVector OwnerLocation,
		FVector OwnerDirection,
		FVector& OutStartPosition,
		FVector& OutDirection);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	void GetVectorsMuzzle(
		FVector MuzzleLocation,
		FVector MuzzleDirection,
		FVector& OutStartPosition,
		FVector& OutDirection);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	void GetVectorsMuzzleOwner(
		FVector OwnerLocation,
		FVector OwnerDirection,
		FVector MuzzleLocation,
		FVector& OutStartPosition,
		FVector& OutDirection);
};
