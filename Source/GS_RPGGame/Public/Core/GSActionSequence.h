#pragma once

#include "CoreMinimal.h"
#include "Core/GSAction.h"
#include "Core/IGSActionsSequenceStrategy.h"
#include "GSActionSequence.generated.h"

UENUM(BlueprintType)
enum class EExecutionSequenceMode : uint8
{
	AllAtOnce,	// Execute all actions at the same time.
	OnebyOne	// Execute the next action when the previous is finished.
};

/**
 * Action which encapsulate a sequence of actions that have to be executed.
 */
UCLASS(Blueprintable)
class GS_RPGGAME_API UGSActionSequence : public UGSAction
{
	GENERATED_BODY()

public:
	UGSActionSequence();

	/**
	* Initialize the action.
	*/
	void Initialize(UGSActionComponent* OwnerActionComp) override;

	/**
	* Starts the action Implementation.
	*/
	void StartAction_Implementation(AActor* Instigator) override;

	/**
	* Stops the action Implementation.
	*/
	void StopAction_Implementation(AActor* Instigator) override;
	
	/**
	* Set the executions mode of the action.
	*/
	void SetExecutionMode(EExecutionSequenceMode NewMode);
protected:
	UPROPERTY(EditAnywhere, Category = "Actions")
	TArray<TSubclassOf<UGSAction>> ActionsToActivate;

	UPROPERTY(BlueprintReadOnly)
	TArray<UGSAction*> Actions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ActionsSequence")
	EExecutionSequenceMode ExecutionMode{EExecutionSequenceMode::AllAtOnce};

private:
	/**
	* Function called on action finished. It will stop the action if all the actions have finished.
	*/
	UFUNCTION()
	void OnActionsFinished(UGSActionComponent* OwningComp, UGSAction* Action);

	UPROPERTY()
	AActor* ActionsInstigator;

	TUniquePtr<IGSActionsSequenceStrategy> ActionsExecutor;
};
