// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../../Gameplay/GameplayTypes.h"
#include "GSInventory.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGSInventory : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GS_RPGGAME_API IGSInventory
{
	GENERATED_BODY()

public:
	/**
	* Adds an item by id.
	*/
	virtual	void AddItem(FName Id) = 0;

	/**
	* Removes an item by id.
	*/
	virtual	void RemoveItem(FName Id) = 0;

	/**
	* Removes an item by index.
	*/
	virtual	void RemoveItem(int Index) = 0;

	/**
	* Sorts the items inside the inventory of the desired type
	*/
	virtual	void SortBy() = 0;

	/**
	* Returns wheter the inventory contaisn the object by id.
	*/
	virtual	bool Contains(FName Id) const = 0;

	/**
	* Returns the item data given an Id
	*/
	virtual FGSItemData GetItemData(FName Id) const = 0;

	/**
	* Returns the item data given an index
	*/
	virtual FGSItemData GetItemData(int Index) const = 0;

	/**
	* Returns the item stacks given an Id
	*/
	virtual unsigned int GetStacks(FName Id) const = 0;

	/**
	* Returns the item stacks given an index
	*/
	virtual unsigned int GetStacks(int Index) const = 0;
};
