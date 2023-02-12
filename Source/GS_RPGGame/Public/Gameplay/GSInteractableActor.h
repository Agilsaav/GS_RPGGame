#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gameplay/GSInteractable.h"
#include "GSInteractableActor.generated.h"

class USphereComponent;
class UGSInteractionComponent;


/**
 * Base class for an interactable object. The main function of this is to be spawned in the world to be interacted with.
 */
UCLASS()
class GS_RPGGAME_API AGSInteractableActor : public AActor, public IGSInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGSInteractableActor();

	/**
	* Main function for interaction with the object
	*/
	void Interact_Implementation(APawn* InstigatorPawn);

	/**
	* Returns the minimum distance to interact
	*/
	float GetInteractDistance_Implementation();

	/**
	* Returns the Interaction text description
	*/
	FText GetInteractText_Implementation(APawn* InstigatorPawn);

protected:
	UPROPERTY(EditAnywhere, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(EditAnywhere, Category = "Interaction")
	float InteractionDistance{250.0f};

private:
	// Allow actors to initialize themselves after all of their components have been initialized
	void PostInitializeComponents() override;

	/**
	* Gets the interaction component from an actor. If it does not exist return nullptr
	*/
	UGSInteractionComponent* GetInteractionComp(AActor* OtherActor) const;

	// Overlap begin function
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Overlap end function
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
