#include "Core/GSAttributesChangeAction.h"
#include "Components/GSActionComponent.h"
#include "Core/GSAttributeSet.h"

void UGSAttributesChangeAction::CreateAttributesModifications(TArray<FAttributeModification> NewAttributesMods)
{
	AttributesMods = MoveTemp(NewAttributesMods);
}

void UGSAttributesChangeAction::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	for (FAttributeModification& CurrentMod : AttributesMods)
	{
		CurrentMod.InstigatorComponent = ActionComp;
		ActionComp->AttributesSet->ApplyAttributeChange(CurrentMod);
	}
}

void UGSAttributesChangeAction::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);

	for (FAttributeModification& CurrentMod : AttributesMods)
	{
		CurrentMod.InstigatorComponent = ActionComp;
		CurrentMod.AttributeValue *= (-1.0f);
		ActionComp->AttributesSet->ApplyAttributeChange(CurrentMod);
	}
}