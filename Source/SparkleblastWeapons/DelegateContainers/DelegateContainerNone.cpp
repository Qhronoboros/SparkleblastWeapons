// Fill out your copyright notice in the Description page of Project Settings.


#include "DelegateContainerNone.h"

void UDelegateContainerNone::BindFunctor(FOnDelegateNone functor)
{
	Delegates.Add(functor);
}

void UDelegateContainerNone::UnbindFunctor(FOnDelegateNone functor)
{
	Delegates.Remove(functor);
}

void UDelegateContainerNone::ExecuteDelegates()
{
	for (FOnDelegateNone Delegate : Delegates)
	{
		Delegate.ExecuteIfBound();
	}
}