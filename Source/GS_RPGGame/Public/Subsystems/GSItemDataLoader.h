#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ItemDataLoader/IGSItemDataLoader.h"
#include "GSItemDataLoader.generated.h"

class UGSActionComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquipmentLoaded, FGSItemDataLoadedContext, DataLoadedContext);

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class GS_RPGGAME_API UGSItemDataLoader : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UGSItemDataLoader();

	bool ShouldCreateSubsystem(UObject* Outer) const override;

	/**
	* Loads an item from the corresponding data table.
	*/
	FGSItemData LoadItem(FName ItemId, EGSItemType ItemType) const;

	/**
	* Loads an item using the Asset Manager
	*/
	void LoadItem(FPrimaryAssetId LoadedId, AActor* ItemOwner, FGSItemDataLoadedContext Context);

	FOnEquipmentLoaded OnItemLoaded;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Items")
	TMap<EGSItemType, UDataTable*> ItemsData;

private:
	/**
	* Function called when the asset manager finishes loading the item
	*/
	void OnItemDataLoaded(FPrimaryAssetId LoadedId, AActor* ItemOwner, FGSItemDataLoadedContext Context) const;

	TMap<EGSItemType, TUniquePtr<IGSItemDataLoader>> ItemsLoaders;
};
