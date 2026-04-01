// Fill out your copyright notice in the Description page of Project Settings.


#include "DelegateContainerVecVec.h"

void UDelegateContainerVecVec::BindFunctor(FOnDelegateVecVec functor)
{
	Delegates.Add(functor);
}

void UDelegateContainerVecVec::UnbindFunctor(FOnDelegateVecVec functor)
{
	Delegates.Remove(functor);
}

void UDelegateContainerVecVec::ExecuteDelegates(FVector Vec1, FVector Vec2)
{
	for (FOnDelegateVecVec Delegate : Delegates)
	{
		Delegate.ExecuteIfBound(Vec1, Vec2);
	}
}