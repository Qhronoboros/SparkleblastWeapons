// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
enum class EArithmeticOperator : uint8
{
    Add UMETA(DisplayName = "Addition"),
    Subtract UMETA(DisplayName = "Subtraction"),
    Multiply UMETA(DisplayName = "Multiplication"),
    Divide UMETA(DisplayName = "Division")
};
