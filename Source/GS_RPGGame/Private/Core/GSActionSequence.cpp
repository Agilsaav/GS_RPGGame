#include "Core/GSActionSequence.h"
#include "Components/GSActionComponent.h"
#include "Core/GSSequenceStrategyAllAtOnce.h"
#include "Core/GSSequenceStrategyOneByOne.h"

UGSActionSequence::UGSActionSequence()
{
	ActionsExecutor = MakeUnique<GSSequenceStrategyAllAtOnce>();
}

void UGSActionSequence::Initialize(UGSActionComponent* OwnerActionComp)
{
	Super::Initialize(OwnerActionComp);

	for (const auto ActionClass : ActionsToActivate)
	{
		UGSAction* ActionToAdd = NewObject<UGSAction>(ActionComp->GetOwner(), ActionClass);
		ActionToAdd->Initialize(ActionComp);
		Actions.Add(ActionToAdd);
	}
}

void UGSActionSequence::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	ActionsInstigator = Instigator;
	ActionComp->OnActionStopped.AddDynamic(this, &UGSActionSequence::OnActionsFinished);

	ActionsExecutor->StartActions(ActionComp, Actions);
}

void UGSActionSequence::StopAction_Implementation(AActor* Instigator)
{
	ActionsExecutor->StopActions(ActionComp, Actions);

	Super::StopAction_Implementation(Instigator);
}

void UGSActionSequence::SetExecutionMode(EExecutionSequenceMode NewMode)
{
	// TODO: Refactor to a factory if it grows
	if (ExecutionMode != NewMode)
	{
		ExecutionMode = NewMode;
		if (ExecutionMode == EExecutionSequenceMode::AllAtOnce)
		{
			ActionsExecutor.Reset(new GSSequenceStrategyAllAtOnce());
		}
		else if (ExecutionMode == EExecutionSequenceMode::OnebyOne)
		{
			ActionsExecutor.Reset(new GSSequenceStrategyOneByOne());
		}
	}
}

void UGSActionSequence::OnActionsFinished(UGSActionComponent* OwningComp, UGSAction* Action)
{
	//TODO: Improve event to not have to check for the action
	if (ActionsExecutor)
	{
		ActionsExecutor->OnActionFinished(OwningComp, Action);
	}

	if (Action == Actions.Last())
	{
		StopAction(ActionComp->GetOwner());
	}
}
