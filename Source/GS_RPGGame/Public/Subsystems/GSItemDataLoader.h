#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Gameplay/GameplayTypes.h"
#include "GSItemDataLoader.generated.h"

class UGSActionComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquipmentLoaded, EGSEquipableType, EquipmentType);

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class GS_RPGGAME_API UGSItemDataLoader : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	bool ShouldCreateSubsystem(UObject* Outer) const override;

	/**
	* Loads an item from the corresponding data table.
	*/
	FGSItemData LoadItem(FName ItemId, EGSItemType ItemType) const;

	/**
	* Loads an equipmment using the Asset Manager
	*/
	void LoadEquipment(FPrimaryAssetId EquipmentClassData, AActor* EquipmentOwner, EGSEquipableType EquipmentType);

	FOnEquipmentLoaded OnEquipmentLoaded;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Items")
	TMap<EGSItemType, UDataTable*> ItemsData;

private:
	/**
	* Function called when the asset manager finishes loading the equipment
	*/
	void OnEquipmentDataLoaded(FPrimaryAssetId LoadedId, AActor* EquipmentOwner, EGSEquipableType EquipmentType) const;
};
