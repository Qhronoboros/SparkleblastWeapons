// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DelegateContainerNone.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnDelegateNone);

// Container for functors with no parameters
UCLASS( BlueprintType )
class SPARKLEBLASTWEAPONS_API UDelegateContainerNone : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void BindFunctor(FOnDelegateNone Functor);

	UFUNCTION(BlueprintCallable)
	void UnbindFunctor(FOnDelegateNone Functor);

	UFUNCTION(BlueprintCallable)
	void InvokeFunctors();

private:
	UPROPERTY(VisibleAnywhere)
	TArray<FOnDelegateNone> Functors;
};
