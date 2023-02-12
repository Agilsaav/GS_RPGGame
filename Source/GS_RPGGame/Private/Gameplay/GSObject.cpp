#include "Gameplay/GSObject.h"

void AGSObject::SetOwner(AActor* NewOwner)
{
	ObjOwner = NewOwner;
}

void AGSObject::InteractWith_Implementation(APawn* InstigatorPawn)
{
	// Implement in children
}
