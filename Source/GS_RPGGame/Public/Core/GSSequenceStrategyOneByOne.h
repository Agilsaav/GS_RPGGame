#pragma once

#include "CoreMinimal.h"
#include "Core/IGSActionsSequenceStrategy.h"

/**
 * Executes the actions one by one waiting for the current to finish.
 */
class GS_RPGGAME_API GSSequenceStrategyOneByOne : public IGSActionsSequenceStrategy
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
	* Function called on action finished. It starts the next action.
	*/
	void OnActionFinished(UGSActionComponent* OwningComp, UGSAction* Action) override;

private:
	TArray<UGSAction*> ActionsToExecute;
	uint8 CurrentActionIndex{0};
};
