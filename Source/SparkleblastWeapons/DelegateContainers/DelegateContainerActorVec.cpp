// Fill out your copyright notice in the Description page of Project Settings.


#include "DelegateContainerActorVec.h"

void UDelegateContainerActorVec::BindFunctor(FOnDelegateActorVec Functor)
{
	Functors.Add(Functor);
}

void UDelegateContainerActorVec::UnbindFunctor(FOnDelegateActorVec Functor)
{
	Functors.Remove(Functor);
}

void UDelegateContainerActorVec::InvokeFunctors(AActor* Actor, FVector Vec)
{
	for (FOnDelegateActorVec Functor : Functors)
	{
		Functor.ExecuteIfBound(Actor, Vec);
	}
}