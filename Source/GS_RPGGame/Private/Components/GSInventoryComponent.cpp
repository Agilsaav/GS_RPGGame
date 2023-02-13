#include "Components/GSInventoryComponent.h"
#include "Core/Inventory/GSNonStackableInventory.h"
#include "Core/Inventory/GSStackableInventory.h"


UGSInventoryComponent::UGSInventoryComponent()
{
}

void UGSInventoryComponent::PostLoad()
{
	Super::PostLoad();

	//Initialazing the inventories here GetOwner() was not correct!
}

void UGSInventoryComponent::CreateInventories()
{
	// TODO: Investigate UFactory or create a factory by myself
	Inventories.Add(EGSItemType::Usable, NewObject<UGSStackableInventory>(GetOwner()));
	Inventories.Add(EGSItemType::Resource, NewObject<UGSStackableInventory>(GetOwner()));
	Inventories.Add(EGSItemType::Food, NewObject<UGSStackableInventory>(GetOwner()));
	Inventories.Add(EGSItemType::Others, NewObject<UGSStackableInventory>(GetOwner()));
	Inventories.Add(EGSItemType::Weapon, NewObject<UGSNonStackableInventory>(GetOwner()));
	Inventories.Add(EGSItemType::Armor, NewObject<UGSNonStackableInventory>(GetOwner()));
	Inventories.Add(EGSItemType::KeyItem, NewObject<UGSNonStackableInventory>(GetOwner()));

	// Remove with factory
	Cast<UGSStackableInventory>(Inventories[EGSItemType::Usable])->ItemType = EGSItemType::Usable;
	Cast<UGSStackableInventory>(Inventories[EGSItemType::Resource])->ItemType = EGSItemType::Resource;
	Cast<UGSStackableInventory>(Inventories[EGSItemType::Food])->ItemType = EGSItemType::Food;
	Cast<UGSStackableInventory>(Inventories[EGSItemType::Others])->ItemType = EGSItemType::Others;
	Cast<UGSNonStackableInventory>(Inventories[EGSItemType::Weapon])->ItemType = EGSItemType::Weapon;
	Cast<UGSNonStackableInventory>(Inventories[EGSItemType::Armor])->ItemType = EGSItemType::Armor;
	Cast<UGSNonStackableInventory>(Inventories[EGSItemType::KeyItem])->ItemType = EGSItemType::KeyItem;

	bInventoriesInitialized = true;
}

void UGSInventoryComponent::AddItem(FName Id, EGSItemType ItemType)
{
	// I do not like this lazy initialization but it works, with the GetWorld problem, I would leave it right now
	// TODO: Find another way and remove the checks on the functions
	if (!bInventoriesInitialized)
	{
		CreateInventories();
	}

	Cast<IGSInventory>(Inventories[ItemType])->AddItem(Id);
}

void UGSInventoryComponent::RemoveItemById(FName Id, EGSItemType ItemType)
{
	if (!bInventoriesInitialized)
	{
		return;
	}

	Cast<IGSInventory>(Inventories[ItemType])->RemoveItem(Id);
}

void UGSInventoryComponent::RemoveItemByIndex(int Index, EGSItemType ItemType)
{
	if (!bInventoriesInitialized)
	{
		return;
	}

	Cast<IGSInventory>(Inventories[ItemType])->RemoveItem(Index);
}

void UGSInventoryComponent::SortBy(EGSItemType ItemType)
{
	if (!bInventoriesInitialized)
	{
		return;
	}

	Cast<IGSInventory>(Inventories[ItemType])->SortBy();
}

bool UGSInventoryComponent::Contains(FName Id, EGSItemType ItemType) const
{
	if (!bInventoriesInitialized)
	{
		return false;
	}

	return Cast<IGSInventory>(Inventories[ItemType])->Contains(Id);
}

FGSItemData UGSInventoryComponent::GetItemData(FName Id, EGSItemType ItemType) const
{
	if (!bInventoriesInitialized)
	{
		return FGSItemData{};
	}

	return Cast<IGSInventory>(Inventories[ItemType])->GetItemData(Id);
}

FGSItemData UGSInventoryComponent::GetItemDataByIndex(int Index, EGSItemType ItemType) const
{
	if (!bInventoriesInitialized)
	{
		return FGSItemData{};
	}

	return Cast<IGSInventory>(Inventories[ItemType])->GetItemData(Index);
}

int UGSInventoryComponent::GetStacks(FName Id, EGSItemType ItemType) const
{
	if (!bInventoriesInitialized)
	{
		return 0;
	}

	return Cast<IGSInventory>(Inventories[ItemType])->GetStacks(Id);
}

int UGSInventoryComponent::GetStacksByIndex(int Index, EGSItemType ItemType) const
{
	if (!bInventoriesInitialized)
	{
		return 0;
	}

	return Cast<IGSInventory>(Inventories[ItemType])->GetStacks(Index);
}
