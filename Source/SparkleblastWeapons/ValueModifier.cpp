#include "ValueModifier.h"
// Fill out your copyright notice in the Description page of Project Settings.

FString UValueModifier::GetModifyDescription()
{
	FString OperatorString = "";
	// Maybe make this a strategy pattern with DataAsset
	switch (Operator)
	{
	case EArithmeticOperator::Add:
		OperatorString = "+";
		break;
	case EArithmeticOperator::Subtract:
		OperatorString = "-";
		break;
	case EArithmeticOperator::Multiply:
		OperatorString = "x";
		break;
	case EArithmeticOperator::Divide:
		OperatorString = "/";
		break;
	default:
		OperatorString = "?";
		break;
	}

	FString Output = "Priority " + FString::Printf(TEXT("%d"), Priority) + " - " + BlackboardKey +
			" " + OperatorString + FString::SanitizeFloat(ChangingValue);

	return Output;
}

float UValueModifier::ApplyMod(float Value)
{
	// Maybe make this a strategy pattern with DataAsset
	switch (Operator)
	{
	case EArithmeticOperator::Add:
		return Value + ChangingValue;
		break;
	case EArithmeticOperator::Subtract:
		return Value - ChangingValue;
		break;
	case EArithmeticOperator::Multiply:
		return Value * ChangingValue;
		break;
	case EArithmeticOperator::Divide:
		return Value / ChangingValue;
		break;
	default:
		return Value;
		break;
	}
}