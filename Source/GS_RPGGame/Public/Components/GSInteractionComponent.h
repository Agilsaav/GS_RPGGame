#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GSInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GS_RPGGAME_API UGSInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	/**
	* Starts looking for interactables
	*/
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void StartLookingForInteractables();

	/**
	* Stops looking for interactables
	*/
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void StopLookingForInteractables();

	/**
	* Sets the trace distance for the ray trace
	*/
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void SetTraceDistance(float NewDistance);

	/**
	* Sets the trace radius for the ray trace
	*/
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void SetTraceRadius(float NewRadius);

	/**
	* Sets the trace radius for the ray trace
	*/
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	float GetTraceDistance() const;

	/**
	* Adds an interactable to the counter.
	*/
	void AddInteractable();

	/**
	* Remove an interactable to the counter.
	*/
	void RemoveInteractable();

	/**
	* Returns if is active.
	*/
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	bool IsRunning() const;

	/**
	* Returns if the component can stop looking for interactables.
	*/
	bool CanStop() const;

	/**
	* Main function to interact with focusedObject.
	*/
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Interact();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	TEnumAsByte<ECollisionChannel> CollisionChannel{ECC_WorldDynamic};

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float TraceDistance{500.0f};

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float TraceRadius{30.0f};

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float InteractFrequency{0.1f};

private:
	/**
	* Finds the object to interact with
	*/
	void FindBestInteractable();

	/**
	* Spawn the main widget for interaction
	*/
	void SpawnInteractionWidget();

	/**
	* Removes the main widget for interaction
	*/
	void RemoveInteractionWidget();

	UPROPERTY()
	AActor* FocusedActor{nullptr};

	FTimerHandle TimerHandle_Interact;
	uint32 CurrentNumberOfInteractables{0};
	bool bIsRunning{false};
};
