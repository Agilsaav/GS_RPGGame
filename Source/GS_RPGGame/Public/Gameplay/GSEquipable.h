#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GSEquipable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGSEquipable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GS_RPGGAME_API IGSEquipable
{
	GENERATED_BODY()
public:
	/**
	* Main function for equipping an object.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Equip(APawn* InstigatorPawn);

	/**
	* Main function for equipping an object.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UnEquip(APawn* InstigatorPawn);
};
