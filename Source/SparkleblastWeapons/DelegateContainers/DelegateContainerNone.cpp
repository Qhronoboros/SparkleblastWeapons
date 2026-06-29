// Fill out your copyright notice in the Description page of Project Settings.


#include "DelegateContainerNone.h"

void UDelegateContainerNone::BindFunctor(FOnDelegateNone Functor)
{
	Functors.Add(Functor);
}

void UDelegateContainerNone::UnbindFunctor(FOnDelegateNone Functor)
{
	Functors.Remove(Functor);
}

void UDelegateContainerNone::InvokeFunctors()
{
	for (FOnDelegateNone Functor : Functors)
	{
		Functor.ExecuteIfBound();
	}
}