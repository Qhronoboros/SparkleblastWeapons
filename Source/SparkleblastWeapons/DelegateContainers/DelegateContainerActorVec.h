// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DelegateContainerActorVec.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDelegateActorVec, AActor*, Actor, FVector, Vec);

// A custom way to invoke blueprint functions outside of C++
// Container for functors with AActor* and Vector as parameters
UCLASS( BlueprintType, DefaultToInstanced )
class SPARKLEBLASTWEAPONS_API UDelegateContainerActorVec : public UObject
{
	GENERATED_BODY()

public:
	// Binds the given functor to this delegate
	UFUNCTION(BlueprintCallable)
	void BindFunctor(FOnDelegateActorVec Functor);

	// Unbinds the given functor to this delegate
	UFUNCTION(BlueprintCallable)
	void UnbindFunctor(FOnDelegateActorVec Functor);

	// Invokes all functors with given parameters
	UFUNCTION(BlueprintCallable)
	void InvokeFunctors(AActor* Actor, FVector Vec);

private:
	// Array of functors that will get invoked
	UPROPERTY(VisibleAnywhere)
	TArray<FOnDelegateActorVec> Functors;
};
