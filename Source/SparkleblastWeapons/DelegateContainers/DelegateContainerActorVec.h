// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DelegateContainerActorVec.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDelegateActorVec, AActor*, Actor, FVector, Vec);

// Container for functors with AActor* and Vector as parameters
UCLASS( BlueprintType, DefaultToInstanced )
class SPARKLEBLASTWEAPONS_API UDelegateContainerActorVec : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void BindFunctor(FOnDelegateActorVec Functor);

	UFUNCTION(BlueprintCallable)
	void UnbindFunctor(FOnDelegateActorVec Functor);

	UFUNCTION(BlueprintCallable)
	void InvokeFunctors(AActor* Actor, FVector Vec);

private:
	UPROPERTY(VisibleAnywhere)
	TArray<FOnDelegateActorVec> Functors;
};
