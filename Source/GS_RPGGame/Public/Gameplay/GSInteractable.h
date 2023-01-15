#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GSInteractable.generated.h"

UINTERFACE(MinimalAPI)
class UGSInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Base interface for an interactable object
 */
class GS_RPGGAME_API IGSInteractable
{
	GENERATED_BODY()

public:
	/**
	* Main function for interaction with the object
	*/ 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact(APawn* InstigatorPawn);

	/**
	* Returns the minimum distance to interact
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float GetInteractDistance();

	/**
	* Returns the Interaction text description
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FText GetInteractText(APawn* InstigatorPawn);
};
