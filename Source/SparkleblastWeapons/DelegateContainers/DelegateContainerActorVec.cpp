// Fill out your copyright notice in the Description page of Project Settings.


#include "DelegateContainerActorVec.h"

void UDelegateContainerActorVec::BindFunctor(FOnDelegateActorVec functor)
{
	Delegates.Add(functor);
}

void UDelegateContainerActorVec::UnbindFunctor(FOnDelegateActorVec functor)
{
	Delegates.Remove(functor);
}

void UDelegateContainerActorVec::ExecuteDelegates(AActor* Actor, FVector Vec)
{
	for (FOnDelegateActorVec Delegate : Delegates)
	{
		Delegate.ExecuteIfBound(Actor, Vec);
	}
}