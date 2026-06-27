// Fill out your copyright notice in the Description page of Project Settings.


#include "ValueModifier.h"

float UValueModifier::Modify(float Value)
{
	// Maybe make this a strategy pattern with DataAsset
	switch (operate)
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
