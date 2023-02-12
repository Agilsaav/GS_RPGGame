#include "Core/Inventory/GSNonStackableInventory.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/GSItemDataLoader.h"
#include "Game/GSGameMode.h"

void UGSNonStackableInventory::AddItem(FName Id)
{
	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UGSItemDataLoader* DataLoader = GameInstance->GetSubsystem<UGSItemDataLoader>();
	FGSItemData Item = DataLoader->LoadItem(Id, ItemType);
	if (!Item.Id.IsNone())
	{
		Items.Add(Item);
	}
}

void UGSNonStackableInventory::RemoveItem(FName Id)
{
	RemoveItem(Items.IndexOfByPredicate([&Id](const FGSItemData& Item) {return Item.Id == Id; }));
}

void UGSNonStackableInventory::RemoveItem(int Index)
{
	if (Index > INDEX_NONE && Index < Items.Num())
	{
		// Swap with last element, remove, don't change allocation.
		Items.RemoveAtSwap(Index, 1, false);
	}
}

void UGSNonStackableInventory::SortBy()
{

}

bool UGSNonStackableInventory::Contains(FName Id) const
{
	return Items.ContainsByPredicate([&Id](const FGSItemData& Item) {return Item.Id == Id;});
}

UWorld* UGSNonStackableInventory::GetWorld() const
{
	// Outer is set when creating action via NewObject<T>
	AActor* Actor = Cast<AActor>(GetOuter());
	if (Actor)
	{
		return Actor->GetWorld();
	}

	return nullptr;
}