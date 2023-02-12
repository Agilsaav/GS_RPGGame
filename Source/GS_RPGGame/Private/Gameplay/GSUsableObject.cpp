#include "Gameplay/GSUsableObject.h"

void AGSUsableObject::Use_Implementation(APawn* InstigatorPawn)
{
	// Implement on childs.
}

void AGSUsableObject::InteractWith_Implementatio(APawn* InstigatorPawn)
{
	Use(InstigatorPawn);
}