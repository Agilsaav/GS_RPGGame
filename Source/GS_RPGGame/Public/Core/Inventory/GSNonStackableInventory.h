#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GSInventory.h"
#include "GSNonStackableInventory.generated.h"

static constexpr unsigned int ONE_STACK = 1;

/**
 * 
 */
UCLASS()
class GS_RPGGAME_API UGSNonStackableInventory : public UObject, public IGSInventory
{
	GENERATED_BODY()
	
public:
	/**
	* Adds an item by id.
	*/
	void AddItem(FName Id) override;

	/**
	* Removes an item by id.
	*/
	void RemoveItem(FName Id) override;

	/**
	* Removes an item by index.
	*/
	void RemoveItem(int Index) override;

	/**
	* Sorts the items inside the inventory of the desired type
	*/
	void SortBy() override;

	/**
	* Returns wheter the inventory contaisn the object by id.
	*/
	UE_NODISCARD bool Contains(FName Id) const override;

	/**
	* Returns the item data given an Id
	*/
	FGSItemData GetItemData(FName Id) const override;

	/**
	* Returns the item data given an index
	*/
	FGSItemData GetItemData(int Index) const override;

	/**
	* Returns the item stacks given an Id
	*/
	unsigned int GetStacks(FName Id) const override { return ONE_STACK; };

	/**
	* Returns the item stacks given an index
	*/
	unsigned int GetStacks(int Index) const override { return ONE_STACK; };

	UWorld* GetWorld() const override;

	EGSItemType ItemType;
private:
	TArray<FGSItemData> Items;
};
