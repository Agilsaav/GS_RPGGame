#include "Gameplay/GSInteractableActor.h"
#include "Components/SphereComponent.h"
#include "Components/GSInteractionComponent.h"
#include "GSCharacter.h"

AGSInteractableActor::AGSInteractableActor()
{
    SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;

    SphereComp->InitSphereRadius(InteractionDistance);
    SphereComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SphereComp->SetCollisionProfileName(TEXT("Interactable"));
}

void AGSInteractableActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AGSInteractableActor::OnOverlapBegin);
	SphereComp->OnComponentEndOverlap.AddDynamic(this, &AGSInteractableActor::OnOverlapEnd);
}

void AGSInteractableActor::Interact_Implementation(APawn* InstigatorPawn)
{
	// Implement in children
}

float AGSInteractableActor::GetInteractDistance_Implementation()
{
	return InteractionDistance;
}

FText AGSInteractableActor::GetInteractText_Implementation(APawn* InstigatorPawn)
{
	return FText();
}

UGSInteractionComponent* AGSInteractableActor::GetInteractionComp(AActor* OtherActor) const
{
	const AGSCharacter* Character = Cast<AGSCharacter>(OtherActor);
	if (Character)
	{
		return Character->GetInteractionComponent();
	}
	return nullptr;
}

void AGSInteractableActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UGSInteractionComponent* InteractionComp = GetInteractionComp(OtherActor))
	{
		InteractionComp->AddInteractable();
		if (!InteractionComp->IsRunning())
		{
			InteractionComp->StartLookingForInteractables();
		}
	}
}

void AGSInteractableActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (UGSInteractionComponent * InteractionComp  = GetInteractionComp(OtherActor))
	{
		InteractionComp->RemoveInteractable();
		if (InteractionComp->IsRunning() && InteractionComp->CanStop())
		{
			InteractionComp->StopLookingForInteractables();
		}
	}
}
