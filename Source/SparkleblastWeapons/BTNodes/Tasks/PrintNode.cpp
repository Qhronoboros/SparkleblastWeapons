// Fill out your copyright notice in the Description page of Project Settings.


#include "PrintNode.h"

NodeStatus UPrintNode::Update()
{
	UE_LOG(LogTemp, Display, TEXT("%s"), *PrintText);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("%s"), *PrintText));
	}

	return NodeStatus::Success;
}