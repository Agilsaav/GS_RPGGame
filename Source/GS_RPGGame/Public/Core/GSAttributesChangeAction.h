#pragma once

#include "CoreMinimal.h"
#include "Core/GSAction.h"
#include "Core/GSAttribute.h"
#include "GSAttributesChangeAction.generated.h"

/**
 * 
 */
UCLASS()
class GS_RPGGAME_API UGSAttributesChangeAction : public UGSAction
{
	GENERATED_BODY()

public:
	/**
	* Inititalize the action with the Attributes Modifications needed
	*/
	void CreateAttributesModifications(TArray<FAttributeModification> NewAttributesMods);

	/**
	* Starts the action Implementation
	*/
	void StartAction_Implementation(AActor* Instigator) override;

	/**
	* Stops the action Implementation
	*/
	void StopAction_Implementation(AActor* Instigator) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Attributes")
	TArray<FAttributeModification> AttributesMods;
};
