// Fill out your copyright notice in the Description page of Project Settings.


#include "ValueModifier.h"

float UValueModifier::Modify(float Value)
{
	// Maybe make this a strategy pattern with DataAsset
	switch (operate)
	{
	case ArithmeticOperator::Add:
		return Value + ChangingValue;
		break;
	case ArithmeticOperator::Subtract:
		return Value - ChangingValue;
		break;
	case ArithmeticOperator::Multiply:
		return Value * ChangingValue;
		break;
	case ArithmeticOperator::Divide:
		return Value / ChangingValue;
		break;
	default:
		return Value;
		break;
	}
}
