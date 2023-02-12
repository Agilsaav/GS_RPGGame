#include "Gameplay/GSEquipableObject.h"
#include "GSCharacter.h"
#include "Components/GSActionComponent.h"
#include "Core/GSAttributesChangeAction.h"

void AGSEquipableObject::Initialize(UGSAttributesChangeAction* NewAttributesChangeAction, TMap<FGameplayTag, TSubclassOf<UGSAction>> NewActiveActions)
{
	AttributesChangeAction = NewAttributesChangeAction;
	ActiveActions = NewActiveActions;
}

void AGSEquipableObject::Equip_Implementation(APawn* InstigatorPawn)
{
	// TODO: Change, find a way to get the Action component without taking the casting
	UGSActionComponent* ActionComp = Cast<AGSCharacter>(ObjOwner)->GetActionComponent();
	ActionComp->AddAction(ObjOwner, GSEquipableTags[EquipmentType], AttributesChangeAction);

	for (const auto& [Tag, ActiveAction] : ActiveActions)
	{
		ActionComp->AddAction(ObjOwner, Tag, ActiveAction);
	}
}

void AGSEquipableObject::UnEquip_Implementation(APawn* InstigatorPawn)
{
	UGSActionComponent* ActionComp = Cast<AGSCharacter>(ObjOwner)->GetActionComponent();
	if (ActionComp)
	{
		ActionComp->RemoveAction(AttributesChangeAction);

		for (const auto& [Tag, ActiveAction] : ActiveActions)
		{
			ActionComp->RemoveActionByTag(Tag);
		}
	}
}

void AGSEquipableObject::InteractWith_Implementatio(APawn* InstigatorPawn)
{
	bIsEquipped ? UnEquip(InstigatorPawn) : Equip(InstigatorPawn);
}