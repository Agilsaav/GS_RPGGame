#include "Core/GSSequenceStrategyOneByOne.h"
#include "Core/GSAction.h"
#include "Components/GSActionComponent.h"

void GSSequenceStrategyOneByOne::StartActions(UGSActionComponent* OwnerActionComp, const TArray<UGSAction*>& Actions)
{
	if (Actions.Num() > 0)
	{
		ActionsToExecute = Actions;
		if (ensure(Actions[CurrentActionIndex]))
		{
			Actions[CurrentActionIndex]->StartAction(OwnerActionComp->GetOwner());
		}
	}
}

void GSSequenceStrategyOneByOne::StopActions(UGSActionComponent* OwnerActionComp, const TArray<UGSAction*>& Actions)
{
	if (ActionsToExecute[CurrentActionIndex])
	{
		ActionsToExecute[CurrentActionIndex]->StopAction(OwnerActionComp->GetOwner());
	}
}

void GSSequenceStrategyOneByOne::OnActionFinished(UGSActionComponent* OwningComp, UGSAction* Action)
{
	if (Action && ActionsToExecute[CurrentActionIndex] && Action == ActionsToExecute[CurrentActionIndex])
	{
		++CurrentActionIndex;
		if (CurrentActionIndex < ActionsToExecute.Num())
		{
			ActionsToExecute[CurrentActionIndex]->StartAction(OwningComp->GetOwner());
		}
	}
}
