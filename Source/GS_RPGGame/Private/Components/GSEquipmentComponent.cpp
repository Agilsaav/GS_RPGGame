#include "Components/GSEquipmentComponent.h"
#include "Gameplay/GSEquipable.h"
#include "Gameplay/GSEquipableObject.h"

UGSEquipmentComponent::UGSEquipmentComponent()
{
	Equipment.Add(EGSEquipableType::Head, nullptr);
	Equipment.Add(EGSEquipableType::Hands, nullptr);
	Equipment.Add(EGSEquipableType::Chest, nullptr);
	Equipment.Add(EGSEquipableType::Legs, nullptr);
	Equipment.Add(EGSEquipableType::Feet, nullptr);
	Equipment.Add(EGSEquipableType::PrimaryAccesory, nullptr);
	Equipment.Add(EGSEquipableType::PrimaryAccesory, nullptr);
	Equipment.Add(EGSEquipableType::RightHand, nullptr);
	Equipment.Add(EGSEquipableType::LeftHand, nullptr);
}

AGSEquipableObject* UGSEquipmentComponent::GetEquipment(EGSEquipableType EquipmentType) const
{
	return Equipment[EquipmentType];
}

void UGSEquipmentComponent::SetEquipment(EGSEquipableType EquipmentType, AGSEquipableObject* NewItem)
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

AGSEquipableObject* UGSEquipmentComponent::GetPrimaryWeapon(EGSEquipableType EquipmentType) const
{
	return Equipment[EGSEquipableType::RightHand];
}

AGSEquipableObject* UGSEquipmentComponent::GetSecondaryWeapon(EGSEquipableType EquipmentType) const
{
	return Equipment[EGSEquipableType::LeftHand];
}

bool UGSEquipmentComponent::HasMainWeapon() const
{
	return Equipment[EGSEquipableType::RightHand] != nullptr;
}

bool UGSEquipmentComponent::HasSecondaryWeapon() const
{
	return Equipment[EGSEquipableType::LeftHand] != nullptr;
}