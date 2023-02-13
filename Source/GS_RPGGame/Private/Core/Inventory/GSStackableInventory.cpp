#include "Core/Inventory/GSStackableInventory.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/GSItemDataLoader.h"

void UGSStackableInventory::AddItem(FName Id)
{
	FGSStackableItemData* ItemFound = Items.FindByPredicate([&Id](const FGSStackableItemData& Item) {return Item.ItemData.Id == Id; });

	if (ItemFound)
	{
		++(ItemFound->Stacks);
	}
	else
	{
		UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		UGSItemDataLoader* DataLoader = GameInstance->GetSubsystem<UGSItemDataLoader>();
		FGSStackableItemData Item{ DataLoader->LoadItem(Id, ItemType) };
		if (!Item.ItemData.Id.IsNone())
		{
			Items.Add(Item);
		}
	}
}

void UGSStackableInventory::RemoveItem(FName Id)
{
	RemoveItem(Items.IndexOfByPredicate([&Id](const FGSStackableItemData& Item) {return Item.ItemData.Id == Id; }));
}

void UGSStackableInventory::RemoveItem(int Index)
{
	if (Index > INDEX_NONE && Index < Items.Num() && (--Items[Index].Stacks) == 0)
	{
		// Swap with last element, remove, don't change allocation.
		Items.RemoveAtSwap(Index, 1, false);
	}
}

void UGSStackableInventory::SortBy()
{

}

bool UGSStackableInventory::Contains(FName Id) const
{
	return Items.ContainsByPredicate([&Id](const FGSStackableItemData& Item) {return Item.ItemData.Id == Id; });
}

UWorld* UGSStackableInventory::GetWorld() const
{
	// Outer is set when creating action via NewObject<T>
	AActor* Actor = Cast<AActor>(GetOuter());
	if (Actor)
	{
		return Actor->GetWorld();
	}

	return nullptr;
}

FGSItemData UGSStackableInventory::GetItemData(FName Id) const
{
	const FGSStackableItemData* ItemFound = Items.FindByPredicate([&Id](const FGSStackableItemData& Item) {return Item.ItemData.Id == Id; });

	if (ItemFound)
	{
		return (*ItemFound).ItemData;
	}

	return FGSItemData{};
}

FGSItemData UGSStackableInventory::GetItemData(int Index) const
{
	if (Index < Items.Num())
	{
		return Items[Index].ItemData;
	}

	return FGSItemData{};
}

unsigned int UGSStackableInventory::GetStacks(FName Id) const
{
	const FGSStackableItemData* ItemFound = Items.FindByPredicate([&Id](const FGSStackableItemData& Item) {return Item.ItemData.Id == Id; });

	if (ItemFound)
	{
		return (*ItemFound).Stacks;
	}

	return 0;
}

unsigned int UGSStackableInventory::GetStacks(int Index) const
{
	if (Index < Items.Num())
	{
		return Items[Index].Stacks;
	}

	return 0;
}