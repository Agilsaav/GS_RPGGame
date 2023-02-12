#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Gameplay/GameplayTypes.h"
#include "Core/Inventory/GSInventory.h"
#include "GSInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GS_RPGGAME_API UGSInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGSInventoryComponent();

	void PostLoad() override;

	void CreateInventories();

	/**
	* Adds an item by id.
	*/
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItem(FName Id, EGSItemType ItemType);

	/**
	* Removes an item by id.
	*/
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItemById(FName Id, EGSItemType ItemType);

	/**
	* Removes an item by index.
	*/
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItemByIndex(int Index, EGSItemType ItemType);

	/**
	* Sorts the items inside the inventory of the desired type
	*/
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SortBy(EGSItemType ItemType);

	/**
	* Returns wheter the inventory contaisn the object by id.
	*/
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool Contains(FName Id, EGSItemType ItemType) const;

private:
	UPROPERTY()
	TMap<EGSItemType, UObject*> Inventories;

	bool bInventoriesInitialized{false};
};
