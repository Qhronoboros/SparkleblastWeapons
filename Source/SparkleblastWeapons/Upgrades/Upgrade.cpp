#include "Upgrade.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "Upgrade.h"
#include "ModificationApplier.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

FString UUpgrade::GetUpgradeDescription()
{
	FString Output = "";

	for (UValueModifier* Modifier : Modifiers)
	{
		Output += Modifier->GetModifyDescription() + "<br>";
	}

	return Output;
}

void UUpgrade::TransferModifiers(UBlackboardComponent* Blackboard)
{
	for (UValueModifier* Modifier : Modifiers)
	{
		// Check if Blackboard contains the key of the Modifier
		UModificationApplier* ModificationApplier = Cast<UModificationApplier>(Blackboard->GetValueAsObject(FName(Modifier->GetBlackboardKey())));
		if (!ModificationApplier)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s: Blackboard does not have key: %s"), *FString(UTF8_TO_TCHAR(__FUNCTION__)), *Modifier->GetBlackboardKey());
			continue;
		}

		// Add Modifier to the ModificationApplier
		ModificationApplier->AddModifier(Modifier);
	}
}

void UUpgrade::RemoveModifiers(UBlackboardComponent* Blackboard)
{
	for (UValueModifier* Modifier : Modifiers)
	{
		//Blackboard->IsValidKey(FName(Modifier->BlackboardKey));
		// Check if Blackboard contains the key of the Modifier
		UModificationApplier* ModificationApplier = Cast<UModificationApplier>(Blackboard->GetValueAsObject(FName(Modifier->GetBlackboardKey())));
		if (!ModificationApplier)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s: Blackboard does not have key: %s"), *FString(UTF8_TO_TCHAR(__FUNCTION__)), *Modifier->GetBlackboardKey());
			continue;
		}

		// Remove Modifier to the ModificationApplier
		ModificationApplier->RemoveModifier(Modifier);
	}
}
