#include "Components/GSActionComponent.h"
#include "Core/GSAction.h"
#include "Core/GSAttributeSet.h"

UGSActionComponent::UGSActionComponent()
{
	// TODO: Erase this and InitializeComponent. For the moment I will leave it here to remember that I need to set bWantsInitializeComponent to true to call InitializeComponent.
	//bWantsInitializeComponent = true;
}

void UGSActionComponent::PostLoad()
{
	Super::PostLoad();
	AttributesSet = NewObject<UGSAttributeSet>(GetOwner(), AttributesSetClass);
}

void UGSActionComponent::InitializeComponent()
{
	Super::InitializeComponent();
	//AttributesSet = NewObject<UGSAttributeSet>(GetOwner(), AttributesSetClass);
}

void UGSActionComponent::BeginPlay()
{
	Super::BeginPlay();
	AttributesSet->Initialize(this);

	for (const auto& [ActionTag, Action] : DefaultActions)
	{
		AddAction(GetOwner(), ActionTag, Action);
	}
}

void UGSActionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	for (const auto& [ActionTag, Action] : Actions)
	{
		if (Action && Action->IsActive())
		{
			Action->StopAction(GetOwner());
		}
	}
}

void UGSActionComponent::AddAttributeListener(FGameplayTag AttributeTag, const FAttributeChanged& Event, bool bExecute)
{
	AttributeListeners.Emplace(AttributeTag, Event);

	if (bExecute)
	{
		FAttribute Attribute;
		if (ensure(AttributesSet))
		{
			AttributesSet->GetAttribute(AttributeTag, Attribute);
		}
		FAttributeChangeDetails AttributeChangeDetails(this, this, Attribute.GetValue(), Attribute.GetValue(), AttributeTag, EAttributeChangeType::None);
		Event.Execute(AttributeChangeDetails);
	}
}

void UGSActionComponent::RemoveAttributeListener(const FAttributeChanged& Event)
{
	TPair<FGameplayTag, FAttributeChanged>* FoundEvent = AttributeListeners.FindByPredicate([&Event](const TPair<FGameplayTag, FAttributeChanged>& EventPair)
	{
		return EventPair.Value == Event;
	});

	if (FoundEvent)
	{
		// To gain performance try to move the value at the last before remove it
		AttributeListeners.Remove(*FoundEvent);
	}
}

void UGSActionComponent::BroadCastAttributeChanged(const FAttributeChangeDetails& AttributeChangeDetails)
{
	for (const auto& [Tag, AttributeChangeEvent] : AttributeListeners)
	{
		if (Tag.MatchesTag(AttributeChangeDetails.AttributeTag))
		{
			AttributeChangeEvent.Execute(AttributeChangeDetails);
		}
	}
}

void UGSActionComponent::AddAction(AActor* Instigator, FGameplayTag ActionTag, TSubclassOf<UGSAction> ActionClass)
{
	if (!ensure(ActionClass))
	{
		return;
	}

	AddAction(Instigator, ActionTag, NewObject<UGSAction>(GetOwner(), ActionClass));
}

void UGSActionComponent::AddAction(AActor* Instigator, FGameplayTag ActionTag, UGSAction* ActionToAdd)
{
	if (Actions.Contains(ActionTag))
	{
		return;
	}

	ActionToAdd->Initialize(this);
	Actions.Add(ActionTag, ActionToAdd);

	if (ActionToAdd->HasToStartOnCreation() && ActionToAdd->CanStart(Instigator))
	{
		ActionToAdd->StartAction(Instigator);
	}
}

void UGSActionComponent::RemoveAction(UGSAction* ActionToRemove)
{
	for (const auto& [ActionTag, Action] : Actions)
	{
		if (ActionToRemove == Action)
		{
			Actions.Remove(ActionTag);
		}
	}
}

void UGSActionComponent::RemoveActionByTag(FGameplayTag ActionToRemove)
{
	if (Actions.Contains(ActionToRemove))
	{
		Actions.Remove(ActionToRemove);
	}
}

bool UGSActionComponent::StartActionByName(AActor* Instigator, FGameplayTag ActionTag)
{
	if (Actions.Contains(ActionTag))
	{
		UGSAction* Action = Actions[ActionTag];
		if (Action && !Action->CanStart(Instigator))
		{
			Action->StartAction(Instigator);

			return true;
		}
	}

	return false;
}

bool UGSActionComponent::StopActionByName(AActor* Instigator, FGameplayTag ActionTag)
{
	if (Actions.Contains(ActionTag))
	{
		UGSAction* Action = Actions[ActionTag];
		if (Action && Action->IsActive())
		{
			Action->StopAction(Instigator);
			return true;
		}
	}

	return false;
}

bool UGSActionComponent::HasAction(TSubclassOf<UGSAction> ActionClass) const
{
	for (const auto& [ActionTag, Action] : Actions)
	{
		if (Action && Action->IsA(ActionClass))
		{
			return true;
		}
	}

	return false;
}

bool UGSActionComponent::HasActionWithTag(FGameplayTag ActionTag) const
{
	return Actions.Contains(ActionTag);
}

bool UGSActionComponent::IsActionEnabled(FGameplayTag ActionTag) const
{
	if (Actions.Contains(ActionTag))
	{
		return Actions[ActionTag]->IsEnabled();
	}

	return false;
}

bool UGSActionComponent::IsActionActive(FGameplayTag ActionTag) const
{
	if (Actions.Contains(ActionTag))
	{
		return Actions[ActionTag]->IsActive();
	}

	return false;
}

void UGSActionComponent::SetActionEnabled(AActor* Instigator, FGameplayTag ActionTag, bool Enabled) const
{
	if (Actions.Contains(ActionTag))
	{
		return Actions[ActionTag]->SetEnabled(Instigator, Enabled);
	}
}

void UGSActionComponent::AddStoppedActions(AActor* Instigator, FGameplayTagContainer ActionsToStop)
{
	for (auto& Tag : ActionsToStop)
	{
		if (HasActionWithTag(Tag))
		{
			++StoppedActions[Tag];
			StopActionByName(Instigator, Tag);
		}
	}
}

void UGSActionComponent::RestartStoppedActions(AActor* Instigator, FGameplayTagContainer ActionsToStop)
{
	for (auto& Tag : ActionsToStop)
	{
		if (HasActionWithTag(Tag) && StoppedActions.Contains(Tag))
		{
			--StoppedActions[Tag];
			if (StoppedActions[Tag] == 0)
			{
				StopActionByName(Instigator, Tag);
				StoppedActions.Remove(Tag);
			}
		}
	}
}

