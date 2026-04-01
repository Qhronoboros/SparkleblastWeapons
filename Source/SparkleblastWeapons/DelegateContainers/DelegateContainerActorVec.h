// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DelegateContainerActorVec.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDelegateActorVec, AActor*, Actor, FVector, Vec);

UCLASS( BlueprintType, DefaultToInstanced )
class SPARKLEBLASTWEAPONS_API UDelegateContainerActorVec : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void BindFunctor(FOnDelegateActorVec functor);

	UFUNCTION(BlueprintCallable)
	void UnbindFunctor(FOnDelegateActorVec functor);

	UFUNCTION(BlueprintCallable)
	void ExecuteDelegates(AActor* Actor, FVector Vec);

private:
	UPROPERTY(VisibleAnywhere)
	TArray<FOnDelegateActorVec> Delegates;
};
