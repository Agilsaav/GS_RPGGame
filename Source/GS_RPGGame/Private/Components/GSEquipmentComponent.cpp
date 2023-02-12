#include "Components/GSEquipmentComponent.h"
#include "Gameplay/GSEquipable.h"

UGSEquipmentComponent::UGSEquipmentComponent()
{
	Equipment.Add(EGSEquipableType::Head, nullptr);
	Equipment.Add(EGSEquipableType::Hands, nullptr);
	Equipment.Add(EGSEquipableType::Chest, nullptr);
	Equipment.Add(EGSEquipableType::Legs, nullptr);
	Equipment.Add(EGSEquipableType::Feet, nullptr);
	Equipment.Add(EGSEquipableType::PrimaryAccesory, nullptr);
	Equipment.Add(EGSEquipableType::PrimaryAccesory, nullptr);
}

AActor* UGSEquipmentComponent::GetEquipment(EGSEquipableType EquipmentType) const
{
	return Equipment[EquipmentType];
}

void UGSEquipmentComponent::SetEquipment(EGSEquipableType EquipmentType, AActor* NewItem)
{
	if (ensure(NewItem->Implements<UGSEquipable>()))
	{
		Equipment[EquipmentType] = NewItem;
		IGSEquipable::Execute_Equip(Equipment[EquipmentType], Cast<APawn>(GetOwner()));
		OnEquipmentEquipped.Broadcast(EquipmentType);
	}
}

void UGSEquipmentComponent::RemoveEquipment(EGSEquipableType EquipmentType)
{
	if (Equipment[EquipmentType])
	{
		IGSEquipable::Execute_UnEquip(Equipment[EquipmentType], Cast<APawn>(GetOwner()));
		Equipment[EquipmentType] = nullptr;
		OnEquipmentUnEquipped.Broadcast(EquipmentType);
	}
}

bool UGSEquipmentComponent::IsSlotEquipped(EGSEquipableType EquipmentType) const
{
	return Equipment[EquipmentType] != nullptr;
}
