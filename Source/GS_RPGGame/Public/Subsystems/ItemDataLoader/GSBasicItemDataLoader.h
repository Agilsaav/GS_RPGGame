#pragma once

#include "IGSItemDataLoader.h"

class AActor;


/**
* Class for an Equipment Loader
*/
class GSBasicItemDataLoader : public IGSItemDataLoader
{
public:
	/**
	* Function called when the asset manager finishes loading the equipment
	*/
	void OnItemDataLoaded(FPrimaryAssetId LoadedId, AActor* ItemOwner, FGSItemDataLoadedContext Context) const override;
};