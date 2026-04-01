// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DelegateContainerNone.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnDelegateNone);

UCLASS( BlueprintType )
class SPARKLEBLASTWEAPONS_API UDelegateContainerNone : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void BindFunctor(FOnDelegateNone functor);

	UFUNCTION(BlueprintCallable)
	void UnbindFunctor(FOnDelegateNone functor);

	UFUNCTION(BlueprintCallable)
	void ExecuteDelegates();

private:
	UPROPERTY(VisibleAnywhere)
	TArray<FOnDelegateNone> Delegates;
};
