#include "Subsystems/GSItemDataLoader.h"
#include "Engine/AssetManager.h"
#include "Subsystems/ItemDataLoader/GSEquipmentDataLoader.h"
#include "Subsystems/ItemDataLoader/GSBasicItemDataLoader.h"


UGSItemDataLoader::UGSItemDataLoader()
{ 
	ItemsLoaders.Emplace(EGSItemType::Armor, MakeUnique<GSEquipmentDataLoader>());
	ItemsLoaders.Emplace(EGSItemType::Weapon, MakeUnique<GSEquipmentDataLoader>());
	ItemsLoaders.Emplace(EGSItemType::Usable, MakeUnique<GSBasicItemDataLoader>());
	ItemsLoaders.Emplace(EGSItemType::Resource, MakeUnique<GSBasicItemDataLoader>());
	ItemsLoaders.Emplace(EGSItemType::Food, MakeUnique<GSBasicItemDataLoader>());
	ItemsLoaders.Emplace(EGSItemType::Others, MakeUnique<GSBasicItemDataLoader>());
	ItemsLoaders.Emplace(EGSItemType::KeyItem, MakeUnique<GSBasicItemDataLoader>());
}

bool UGSItemDataLoader::ShouldCreateSubsystem(UObject* Outer) const
{
	if (this->GetClass()->IsInBlueprint()) 
	{
		return true; 
	}

	return false;
}

FGSItemData UGSItemDataLoader::LoadItem(FName ItemId, EGSItemType ItemType) const
{
	FGSItemRowInfo* ItemRow = ItemsData[ItemType]->FindRow<FGSItemRowInfo>(ItemId, "Item");

	if (ItemRow)
	{
		ItemRow->ItemData.Id = ItemId;
		return ItemRow->ItemData;
	}
	return FGSItemData{};
}

void UGSItemDataLoader::LoadItem(FPrimaryAssetId LoadedId, AActor* ItemOwner, FGSItemDataLoadedContext Context)
{
	UAssetManager* Manager = UAssetManager::GetIfValid();

	TArray<FName> Bundles;
	FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(this, &UGSItemDataLoader::OnItemDataLoaded, LoadedId, ItemOwner, Context);
	Manager->LoadPrimaryAsset(LoadedId, Bundles, Delegate);
}

void UGSItemDataLoader::OnItemDataLoaded(FPrimaryAssetId LoadedId, AActor* ItemOwner, FGSItemDataLoadedContext Context) const
{
	ItemsLoaders[Context.ItemType]->OnItemDataLoaded(LoadedId, ItemOwner, Context);
	OnItemLoaded.Broadcast(Context);
}