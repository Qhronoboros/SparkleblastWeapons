// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DelegateContainerNone.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnDelegateNone);

// A custom way to invoke blueprint functions outside of C++
// Container for functors with no parameters
UCLASS( BlueprintType )
class SPARKLEBLASTWEAPONS_API UDelegateContainerNone : public UObject
{
	GENERATED_BODY()
	
public:
	// Binds the given functor to this delegate
	UFUNCTION(BlueprintCallable)
	void BindFunctor(FOnDelegateNone Functor);

	// Unbinds the given functor to this delegate
	UFUNCTION(BlueprintCallable)
	void UnbindFunctor(FOnDelegateNone Functor);

	// Invokes all functors
	UFUNCTION(BlueprintCallable)
	void InvokeFunctors();

private:
	// Array of functors that will get invoked
	UPROPERTY(VisibleAnywhere)
	TArray<FOnDelegateNone> Functors;
};
