// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Projectile.h"
#include "ShootType.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class SPARKLEBLASTWEAPONS_API UShootType : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShootType();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxDistance;


public:	
	UFUNCTION()
	bool GetLineTraceHit(FVector location, FVector direction, ECollisionChannel TraceChannel, FHitResult& hit, float DebugLineDuration);
	UFUNCTION()
	bool GetMultiLineTraceHit(FVector location, FVector direction, ECollisionChannel TraceChannel, TArray<FHitResult>& hit, float DebugLineDuration);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	void LineTraceHitscan(const FVector StartPosition, const FVector Direction, FHitResult& Hit, float DebugLineDuration);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	void MultiLineTraceHitscan(const FVector StartPosition, const FVector Direction, TArray<FHitResult>& Hits, float DebugLineDuration);

	UFUNCTION(BlueprintCallable)
	AActor* SpawnProjectile(const FVector StartPosition, const FVector Direction, TSubclassOf<AActor> Projectile);
};
