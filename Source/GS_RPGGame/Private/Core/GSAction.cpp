#include "Core/GSAction.h"
#include "Components/GSActionComponent.h"

void UGSAction::Initialize(UGSActionComponent* OwnerActionComp)
{
	ActionComp = OwnerActionComp;
}

void UGSAction::StartAction_Implementation(AActor* Instigator)
{
	ActionComp->ActiveGameplayTags.AppendTags(GrantsTags);
	ActionComp->AddStoppedActions(Instigator, StopActionTags);
	bIsActive = true;

	ActionComp->OnActionStarted.Broadcast(ActionComp, this);
}

void UGSAction::StopAction_Implementation(AActor* Instigator)
{
	ActionComp->ActiveGameplayTags.RemoveTags(GrantsTags);
	ActionComp->RestartStoppedActions(Instigator, StopActionTags);
	bIsActive = false;

	ActionComp->OnActionStopped.Broadcast(ActionComp, this);
}

bool UGSAction::CanStart_Implementation(AActor* Instigator)
{
	return bIsEnabled && !bIsActive && !(ActionComp->ActiveGameplayTags.HasAny(BlockedTags));
}

void UGSAction::SetEnabled(AActor* Instigator, bool Enabled)
{
	bIsEnabled = Enabled;

	if (bIsEnabled && bAutoStart)
	{
		StartAction(Instigator);
	}
	else if (!bIsEnabled && IsActive())
	{
		StopAction(Instigator);
	}
}

bool UGSAction::IsActive() const
{
	return bIsActive;
}

bool UGSAction::IsEnabled() const
{
	return bIsEnabled;
}


bool UGSAction::HasToStartOnCreation() const
{
	return bAutoStart;
}
