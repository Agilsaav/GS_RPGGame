#include "Components/GSInteractionComponent.h"
#include "Gameplay/GSInteractable.h"
#include "UI/GSWorldWidgetWidget.h"
#include "Components/SphereComponent.h"

void UGSInteractionComponent::StartLookingForInteractables()
{
	GetOwner()->GetWorldTimerManager().SetTimer(TimerHandle_Interact, this, &UGSInteractionComponent::FindBestInteractable, InteractFrequency, true);
	bIsRunning = true;
}

void UGSInteractionComponent::StopLookingForInteractables()
{
	GetOwner()->GetWorldTimerManager().ClearTimer(TimerHandle_Interact);
	bIsRunning = false;
	FocusedActor = nullptr;
}

void UGSInteractionComponent::SetTraceDistance(float NewDistance)
{
	TraceDistance = NewDistance;
}

void UGSInteractionComponent::SetTraceRadius(float NewRadius)
{
	TraceRadius = NewRadius;
}

float UGSInteractionComponent::GetTraceDistance() const
{
	return TraceDistance;
}

void UGSInteractionComponent::AddInteractable()
{
	++CurrentNumberOfInteractables;
}

void UGSInteractionComponent::RemoveInteractable()
{
	--CurrentNumberOfInteractables;
}

bool UGSInteractionComponent::IsRunning() const
{
	return bIsRunning;
}

bool UGSInteractionComponent::CanStop() const
{
	return IsActive() && CurrentNumberOfInteractables == 0;
}

void UGSInteractionComponent::Interact()
{
	if (!FocusedActor || !bIsRunning)
	{
		return;
	}

	IGSInteractable::Execute_Interact(FocusedActor, Cast<APawn>(GetOwner()));
}

void UGSInteractionComponent::FindBestInteractable()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(CollisionChannel);

	AActor* Owner = GetOwner();
	FVector EyeLocation;
	FRotator EyeRotation;
	Owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	const FVector EndLocation = EyeLocation + (TraceDistance * EyeRotation.Vector());

	FCollisionShape Shape;
	Shape.SetSphere(TraceRadius);

	TArray<FHitResult> Hits;
	GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, EndLocation, FQuat::Identity, ObjectQueryParams, Shape);

	const FVector OwnerLocation = GetOwner()->GetActorLocation();
	const FVector OwnerForwardDir = GetOwner()->GetActorForwardVector();
	FocusedActor = nullptr;
	for (const auto& Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		const bool IsSphereComponent = Cast<USphereComponent>(Hit.Component) != nullptr;
		if (HitActor && !IsSphereComponent)
		{
			if (HitActor->Implements<UGSInteractable>() && CanPlayerInteract(HitActor, OwnerLocation, OwnerForwardDir))
			{
				FocusedActor = HitActor;
				break;
			}
		}
	}

	FocusedActor ? SpawnInteractionWidget() : RemoveInteractionWidget();
}

void UGSInteractionComponent::SpawnInteractionWidget()
{
	if (!DefaultWidgetInstance && ensure(DefaultWidgetClass))
	{
		DefaultWidgetInstance = CreateWidget<UGSWorldWidgetWidget>(GetWorld(), DefaultWidgetClass);
	}

	if (DefaultWidgetInstance)
	{
		DefaultWidgetInstance->AttachedActor = FocusedActor;
		if (!DefaultWidgetInstance->IsInViewport())
		{
			DefaultWidgetInstance->AddToViewport();
		}
	}
}

void UGSInteractionComponent::RemoveInteractionWidget()
{
	if (DefaultWidgetInstance)
	{
		DefaultWidgetInstance->RemoveFromParent();
	}
}

bool UGSInteractionComponent::CanPlayerInteract(AActor* OtherActor, const FVector& OwnerLocation, const FVector& OwnerForwardDirection) const
{
	const FVector Direction = OtherActor->GetActorLocation() - OwnerLocation;
	return FVector::Distance(OtherActor->GetActorLocation(), OwnerLocation) <= IGSInteractable::Execute_GetInteractDistance(OtherActor)
		&& FVector::DotProduct(Direction, OwnerForwardDirection) > 0.f;
}

