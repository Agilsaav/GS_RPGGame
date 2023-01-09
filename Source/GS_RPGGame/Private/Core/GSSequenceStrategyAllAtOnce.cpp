#include "Core/GSSequenceStrategyAllAtOnce.h"
#include "Core/GSAction.h"
#include "Components/GSActionComponent.h"

void GSSequenceStrategyAllAtOnce::StartActions(UGSActionComponent* OwnerActionComp, const TArray<UGSAction*>& Actions)
{
	for (const auto Action : Actions)
	{
		AActor* Instigator = OwnerActionComp->GetOwner();
		if (Action && Action->CanStart(Instigator))
		{
			Action->StartAction(Instigator);
		}
	}
}

void GSSequenceStrategyAllAtOnce::StopActions(UGSActionComponent* OwnerActionComp, const TArray<UGSAction*>& Actions)
{
	for (const auto Action : Actions)
	{
		if (Action && Action->IsActive())
		{
			Action->StopAction(OwnerActionComp->GetOwner());
		}
	}
}
