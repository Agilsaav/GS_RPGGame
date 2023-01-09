#pragma once

#include "CoreMinimal.h"
#include "Core/IGSActionsSequenceStrategy.h"

/**
 * Executes all the actions at the start.
 */
class GS_RPGGAME_API GSSequenceStrategyAllAtOnce : public IGSActionsSequenceStrategy
{
public:
	/**
	* Start all the actions.
	*/
	void StartActions(UGSActionComponent* OwnerActionComp, const TArray<UGSAction*>& Actions) override;

	/**
	* Stops all the actions.
	*/
	void StopActions(UGSActionComponent* OwnerActionComp, const TArray<UGSAction*>& Actions) override;

	/**
	* On action finished function.
	*/
	void OnActionFinished(UGSActionComponent* OwningComp, UGSAction* Action) override {};
};
