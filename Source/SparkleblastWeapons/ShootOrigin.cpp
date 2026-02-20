// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootOrigin.h"

// Sets default values for this component's properties
UShootOrigin::UShootOrigin()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UShootOrigin::GetLineTraceHit(FVector Location, FVector Direction, FHitResult& Hit)
{
	FCollisionQueryParams CollisionParams;
	if (!GetWorld()->LineTraceSingleByChannel(Hit, Location, Location + Direction * MaxDistance, ECC_Visibility, CollisionParams)) return false;

	return true;
}

void UShootOrigin::GetVectorsOwner(
	FVector OwnerLocation,
	FVector OwnerDirection,
	FVector& OutStartPosition,
	FVector& OutDirection)
{
	OutStartPosition = OwnerLocation;
	OutDirection = OwnerDirection;
}

void UShootOrigin::GetVectorsMuzzle(
	FVector MuzzleLocation,
	FVector MuzzleDirection,
	FVector& OutStartPosition,
	FVector& OutDirection)
{
	OutStartPosition = MuzzleLocation;
	OutDirection = MuzzleDirection;
}

void UShootOrigin::GetVectorsMuzzleOwner(
	FVector OwnerLocation,
	FVector OwnerDirection,
	FVector MuzzleLocation,
	FVector& OutStartPosition,
	FVector& OutDirection)
{
	OutStartPosition = MuzzleLocation;

	// Default
	OutDirection;

	FHitResult Hit;
	if (!GetLineTraceHit(OwnerLocation, OwnerDirection, Hit))
	{
		UE_LOG(LogTemp, Warning, TEXT("(UShootOrigin::GetVectorsMuzzleOwner) Did not hit any solid object with lineTrace"));

		// If not hitting anything, get the point with the maximum distance
		OutDirection = OwnerDirection * MaxDistance + OwnerLocation - MuzzleLocation;
	}
	else
	{
		OutDirection = Hit.Location - MuzzleLocation;
	}

	OutDirection.Normalize();
}
