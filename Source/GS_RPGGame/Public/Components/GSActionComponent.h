#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/GSAttribute.h"
#include "GSActionComponent.generated.h"

class UGSAttributeSet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionStateChanged, UGSActionComponent*, OwningComp, UGSAction*, Action);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GS_RPGGAME_API UGSActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGSActionComponent();

	void InitializeComponent() override;

	void PostLoad() override;

	/**
	* Adds a listener to an especific attribute.
	*/
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void AddAttributeListener(FGameplayTag AttributeTag, const FAttributeChanged& Event, bool bExecute = false);

	/**
	* Adds a listener to an especific attribute.
	*/
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void RemoveAttributeListener(const FAttributeChanged& Event);

	/**
	* Broadcast an attribute change for all the listeners on the attribute changed.
	*/
	void BroadCastAttributeChanged(const FAttributeChangeDetails& AttributeChangeDetails);

	/**
	* Adds an action.Using a subclass of the action
	*/
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void AddAction(AActor* Instigator, FGameplayTag ActionTag, TSubclassOf<UGSAction> ActionClass);

	/**
	* Adds an action. Using a pointer object to the action
	*/
	void AddAction(AActor* Instigator, FGameplayTag ActionTag, UGSAction* ActionToAdd);

	/**
	* Removes an action given its pointer.
	*/
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void RemoveAction(UGSAction* ActionToRemove);

	/**
	* Removes an action given its tag.
	*/
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void RemoveActionByTag(FGameplayTag ActionToRemove);

	/**
	* Starts an action by tag.
	*/
	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool StartActionByName(AActor* Instigator, FGameplayTag ActionTag);

	/**
	* Stops an action by tag.
	*/
	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool StopActionByName(AActor* Instigator, FGameplayTag ActionTag);

	/**
	* Finds an action using a Subclass of it. Returns true if it is found, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool HasAction(TSubclassOf<UGSAction> ActionClass) const;

	/**
	* Finds an action using a GameplayTag. Returns true if it is found, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool HasActionWithTag(FGameplayTag ActionTag) const;

	/**
	* Finds if an action is Enabled. Returns true if it is enabled, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool IsActionEnabled(FGameplayTag ActionTag) const;

	/**
	* Finds if an action is Active. Returns true if it is enabled, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool IsActionActive(FGameplayTag ActionTag) const;

	/**
	* Enables or Disables an action.
	*/
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void SetActionEnabled(AActor* Instigator, FGameplayTag ActionTag, bool Enabled) const;

	/**
	* Adds the stopped actions to the map, and stop them
	*/
	void AddStoppedActions(AActor* Instigator, FGameplayTagContainer ActionsToStop);

	/**
	* Restart the stopped actions if there is no other action stopping them
	*/
	void RestartStoppedActions(AActor* Instigator, FGameplayTagContainer ActionsToStop);
	
	// TODO: Get action
	UPROPERTY(BlueprintReadWrite)
	UGSAttributeSet* AttributesSet;

	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	FGameplayTagContainer ActiveGameplayTags;

	UPROPERTY(BlueprintAssignable)
	FOnActionStateChanged OnActionStarted;

	UPROPERTY(BlueprintAssignable)
	FOnActionStateChanged OnActionStopped;

protected:
	UPROPERTY(EditAnywhere, Category = "Actions")
	TMap<FGameplayTag, TSubclassOf<UGSAction>> DefaultActions;

	UPROPERTY(EditAnywhere, Category = "Attributes")
	TSubclassOf<UGSAttributeSet> AttributesSetClass;

	UPROPERTY(BlueprintReadOnly)
	TMap<FGameplayTag, UGSAction*> Actions;

private:
	/**
	 * Begin gameplay for this component.
	 */
	void BeginPlay() override;

	/**
	 * Ends gameplay for this component.
	 * Called from AActor::EndPlay only if bHasBegunPlay is true
	 */
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	TArray<TPair<FGameplayTag, FAttributeChanged>> AttributeListeners;
	TMap<FGameplayTag, uint8> StoppedActions;
};
