// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DelegateContainerVecVec.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDelegateVecVec, FVector, Vec1, FVector, Vec2);

UCLASS( BlueprintType )
class SPARKLEBLASTWEAPONS_API UDelegateContainerVecVec : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void BindFunctor(FOnDelegateVecVec functor);

	UFUNCTION(BlueprintCallable)
	void UnbindFunctor(FOnDelegateVecVec functor);

	UFUNCTION(BlueprintCallable)
	void ExecuteDelegates(FVector Vec1, FVector Vec2);

	UPROPERTY(VisibleAnywhere)
	TArray<FOnDelegateVecVec> Delegates;

	UPROPERTY(VisibleAnywhere)
	TArray<int> Integers;
};
