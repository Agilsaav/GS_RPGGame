#pragma once

#include "CoreMinimal.h"
#include "Gameplay/GameplayTypes.h"

class AActor;


/**
* Interface for an Item Loader object
*/
class IGSItemDataLoader
{
public:
	virtual ~IGSItemDataLoader() = default;

	/**
	* Function called when the asset manager finishes loading the equipment
	*/
	virtual void OnItemDataLoaded(FPrimaryAssetId LoadedId, AActor* ItemOwner, FGSItemDataLoadedContext Context) const = 0;
};