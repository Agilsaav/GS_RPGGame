#pragma once

#include "CoreMinimal.h"

class UGSActionComponent;
class UGSAction;

/**
* NOTE: This could habe been done by using an Unreal interface and making the function BlueprintNativeEvent to be
* implemented in BP, but in this case, I wanted the system to be all in C++.
*/

/**
* Interface for the strategies used in thee way to execute an Action Sequence
*/
class IGSActionsSequenceStrategy
{
public:
	virtual ~IGSActionsSequenceStrategy() = default;

	/**
	* Start all the actions.
	*/
	virtual void StartActions(UGSActionComponent* OwnerActionComp, const TArray<UGSAction*>& Actions) = 0;

	/**
	* Stops all the actions.
	*/
	virtual void StopActions(UGSActionComponent* OwnerActionComp, const TArray<UGSAction*>& Actions) = 0;

	/**
	* On action finished function.
	*/
	virtual void OnActionFinished(UGSActionComponent* OwningComp, UGSAction* Action) = 0;
};