#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GSUsable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGSUsable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GS_RPGGAME_API IGSUsable
{
	GENERATED_BODY()

public:
	/**
	* Main function for using an usuable object.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Use(APawn* InstigatorPawn);
};
