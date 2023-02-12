#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GSInventory.h"
#include "GSNonStackableInventory.generated.h"

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
	bool Contains(FName Id) const override;

	UWorld* GetWorld() const override;

	EGSItemType ItemType;
private:
	TArray<FGSItemData> Items;
};
