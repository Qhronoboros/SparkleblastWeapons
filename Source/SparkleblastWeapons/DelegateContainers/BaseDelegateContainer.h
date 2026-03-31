// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseDelegateContainer.generated.h"

DECLARE_DYNAMIC_DELEGATE(FunctionDelegate);

UCLASS( BlueprintType )
class SPARKLEBLASTWEAPONS_API UBaseDelegateContainer : public UObject
{
	GENERATED_BODY()
	
public:	
	UFUNCTION(BlueprintCallable)
	void CreateThread(FunctionDelegate& functor) { functor.ExecuteIfBound(); }

	//virtual void GetDelegate() PURE_VIRTUAL(ABaseDelegateContainer::GetDelegate, );

};
