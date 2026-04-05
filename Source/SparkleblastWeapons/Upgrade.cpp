// Fill out your copyright notice in the Description page of Project Settings.


#include "Upgrade.h"
#include "ModificationApplier.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

void UUpgrade::TransferModifiers(UBlackboardComponent* Blackboard)
{
	for (UValueModifier* Modifier : Modifiers)
	{
		//Blackboard->IsValidKey(FName(Modifier->BlackboardKey));
		// Check if Blackboard contains the key of the Modifier
		AModificationApplier* ModificationApplier = Cast<AModificationApplier>(Blackboard->GetValueAsObject(FName(Modifier->BlackboardKey)));
		if (!ModificationApplier)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s: Blackboard does not have key: %s"), *FString(UTF8_TO_TCHAR(__FUNCTION__)), *Modifier->BlackboardKey);
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
		AModificationApplier* ModificationApplier = Cast<AModificationApplier>(Blackboard->GetValueAsObject(FName(Modifier->BlackboardKey)));
		if (!ModificationApplier)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s: Blackboard does not have key: %s"), *FString(UTF8_TO_TCHAR(__FUNCTION__)), *Modifier->BlackboardKey);
			continue;
		}

		// Remove Modifier to the ModificationApplier
		ModificationApplier->RemoveModifier(Modifier);
	}
}
