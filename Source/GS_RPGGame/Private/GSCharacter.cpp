#include "GSCharacter.h"
#include "Components/GSActionComponent.h"


AGSCharacter::AGSCharacter()
{
	ActionComp = CreateAbstractDefaultSubobject<UGSActionComponent>("ActionComponent");
}

void AGSCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

