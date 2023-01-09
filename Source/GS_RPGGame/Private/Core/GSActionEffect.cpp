#include "Core/GSActionEffect.h"
#include "Components/GSActionComponent.h"

UGSActionEffect::UGSActionEffect()
{
	bAutoStart = true;
}

void UGSActionEffect::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	// On finished stops the action
	if (Duration > 0.0f)
	{
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "StopAction", Instigator);
		GetWorld()->GetTimerManager().SetTimer(DurationHandle, Delegate, Duration, false);
	}

	// Appply effect each period
	if (Period > 0.0f)
	{
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "ExecutePeriodicEffect", Instigator);
		GetWorld()->GetTimerManager().SetTimer(PeriodHandle, Delegate, Period, true);
	}

	TimeStarted = GetWorld()->TimeSeconds;
}

void UGSActionEffect::StopAction_Implementation(AActor* Instigator)
{
	// If the Duration timer executes before the Period we still need to tick one more time:
	if (GetWorld()->GetTimerManager().GetTimerRemaining(PeriodHandle) < KINDA_SMALL_NUMBER)
	{
		ExecutePeriodicEffect(Instigator);
	}

	Super::StopAction_Implementation(Instigator);

	GetWorld()->GetTimerManager().ClearTimer(DurationHandle);
	GetWorld()->GetTimerManager().ClearTimer(PeriodHandle);

	if (ActionComp)
	{
		// We do not have to destroy it: Nobody has a reference to it -> Garbage collector will do it for us!
		ActionComp->RemoveAction(this);
	}
}

float UGSActionEffect::GetTimeRemaining() const
{
	return Duration + TimeStarted - GetWorld()->TimeSeconds;
}

void UGSActionEffect::ExecutePeriodicEffect_Implementation(AActor* Instigator)
{
	// This function is meant to be implemented by childs either in C++ or BP.
}
