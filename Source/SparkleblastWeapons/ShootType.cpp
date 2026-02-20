// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootType.h"

// Sets default values for this component's properties
UShootType::UShootType()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UShootType::GetLineTraceHit(FVector Location, FVector Direction, ECollisionChannel TraceChannel, FHitResult& Hit, float DebugLineDuration)
{
	FCollisionQueryParams CollisionParams;
	if (GetWorld()->LineTraceSingleByChannel(Hit, Location, Location + Direction * MaxDistance, TraceChannel, CollisionParams))
	{
		DrawDebugLine(GetWorld(), Location, Hit.Location, FColor::Blue, false, DebugLineDuration);
		return true;
	}
	else
	{
		DrawDebugLine(GetWorld(), Location, Location + Direction * MaxDistance, FColor::Blue, false, DebugLineDuration);
		return false;
	}
}

bool UShootType::GetMultiLineTraceHit(FVector Location, FVector Direction, ECollisionChannel TraceChannel, TArray<FHitResult>& Hits, float DebugLineDuration)
{
	FCollisionQueryParams CollisionParams;

	if (GetWorld()->LineTraceMultiByChannel(Hits, Location, Location + Direction * MaxDistance, TraceChannel, CollisionParams))
	{
		//DrawDebugLine(GetWorld(), Location, Hits.Last().Location, FColor::Blue, false, DebugLineDuration);
		return true;
	}
	else
	{
		//DrawDebugLine(GetWorld(), Location, Location + Direction * MaxDistance, FColor::Blue, false, DebugLineDuration);
		return false;
	}
}

void UShootType::LineTraceHitscan(const FVector StartPosition, const FVector Direction, FHitResult& Hit, float DebugLineDuration)
{
	if (!GetLineTraceHit(StartPosition, Direction, ECC_Visibility, Hit, DebugLineDuration))
	{
		UE_LOG(LogTemp, Warning, TEXT("(UShootType::LineTraceHitscan) Did not hit any object with lineTrace"));
	}
}

void UShootType::MultiLineTraceHitscan(const FVector StartPosition, const FVector Direction, TArray<FHitResult>& Hits, float DebugLineDuration)
{
	if (!GetMultiLineTraceHit(StartPosition, Direction, ECC_Visibility, Hits, DebugLineDuration))
	{
		UE_LOG(LogTemp, Warning, TEXT("(UShootType::MultiLineTraceHitscan) Did not hit any object with lineTrace"));
	}
}

AActor* UShootType::SpawnProjectile(const FVector StartPosition, const FVector Direction, TSubclassOf<AActor> Projectile)
{
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	return GetWorld()->SpawnActor<AActor>(Projectile, StartPosition, Direction.Rotation(), spawnParams);
}