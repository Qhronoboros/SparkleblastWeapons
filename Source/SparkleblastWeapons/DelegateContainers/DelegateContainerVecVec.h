// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DelegateContainerVecVec.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDelegateVecVec, FVector, Vec1, FVector, Vec2);

// A custom way to invoke blueprint functions outside of C++
// Container for functors with two Vectors as parameters
UCLASS( BlueprintType )
class SPARKLEBLASTWEAPONS_API UDelegateContainerVecVec : public UObject
{
	GENERATED_BODY()

public:
	// Binds the given functor to this delegate
	UFUNCTION(BlueprintCallable)
	void BindFunctor(FOnDelegateVecVec Functor);

	// Unbinds the given functor to this delegate
	UFUNCTION(BlueprintCallable)
	void UnbindFunctor(FOnDelegateVecVec Functor);

	// Invokes all functors with given parameters
	UFUNCTION(BlueprintCallable)
	void InvokeFunctors(FVector Vec1, FVector Vec2);

private:
	// Array of functors that will get invoked
	UPROPERTY(VisibleAnywhere)
	TArray<FOnDelegateVecVec> Functors;
};
