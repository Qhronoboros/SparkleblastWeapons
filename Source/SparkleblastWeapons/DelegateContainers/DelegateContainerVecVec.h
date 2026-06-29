// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DelegateContainerVecVec.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDelegateVecVec, FVector, Vec1, FVector, Vec2);

// Container for functors with two Vectors as parameters
UCLASS( BlueprintType )
class SPARKLEBLASTWEAPONS_API UDelegateContainerVecVec : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void BindFunctor(FOnDelegateVecVec Functor);

	UFUNCTION(BlueprintCallable)
	void UnbindFunctor(FOnDelegateVecVec Functor);

	UFUNCTION(BlueprintCallable)
	void InvokeFunctors(FVector Vec1, FVector Vec2);

private:
	UPROPERTY(VisibleAnywhere)
	TArray<FOnDelegateVecVec> Functors;
};
