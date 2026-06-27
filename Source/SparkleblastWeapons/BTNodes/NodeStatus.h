// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
enum class ENodeStatus : uint8
{
    Success UMETA(DisplayName = "Node Succeeded"),
    Failed UMETA(DisplayName = "Node Failed"),
    Running UMETA(DisplayName = "Node still Running")
};