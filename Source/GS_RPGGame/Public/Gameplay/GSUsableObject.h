#pragma once

#include "CoreMinimal.h"
#include "Gameplay/GSObject.h"
#include "Gameplay/GSUsable.h"
#include "GSUsableObject.generated.h"

/**
 * 
 */
UCLASS()
class GS_RPGGAME_API AGSUsableObject : public AGSObject, public IGSUsable
{
	GENERATED_BODY()
	
public:
	/**
	* Main function for using an usuable object.
	*/
	void Use_Implementation(APawn* InstigatorPawn);

	/**
	* Main function for interaction with the object. Do not confuse with InteractableActors.
	*/
	void InteractWith_Implementatio(APawn* InstigatorPawn);
};
