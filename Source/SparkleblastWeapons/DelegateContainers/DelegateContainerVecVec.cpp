// Fill out your copyright notice in the Description page of Project Settings.


#include "DelegateContainerVecVec.h"

void UDelegateContainerVecVec::BindFunctor(FOnDelegateVecVec Functor)
{
	Functors.Add(Functor);
}

void UDelegateContainerVecVec::UnbindFunctor(FOnDelegateVecVec Functor)
{
	Functors.Remove(Functor);
}

void UDelegateContainerVecVec::InvokeFunctors(FVector Vec1, FVector Vec2)
{
	for (FOnDelegateVecVec Functor : Functors)
	{
		Functor.ExecuteIfBound(Vec1, Vec2);
	}
}