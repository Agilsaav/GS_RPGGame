#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "GSAction.generated.h"

class UGSActionComponent;

/**
 * 
 */
UCLASS(Blueprintable)
class GS_RPGGAME_API UGSAction : public UObject
{
	GENERATED_BODY()
public:
	/**
	* Initialize the action.
	*/
	virtual void Initialize(UGSActionComponent* OwnerActionComp);

	/**
	* Starts the action. Can be implemented in Blueprint.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StartAction(AActor* Instigator);

	/**
	* Stops the action. Can be implemented in Blueprint.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Action")
	void StopAction(AActor* Instigator);

	/**
	* Returns true if the action can start. False otherwise. Can be implemented in Blueprint.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	bool CanStart(AActor* Instigator);

	/**
	* Returns true if the action is active. False otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Action")
	bool IsActive() const;

	/**
	* Returns true if the action is enabled. False otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Action")
	bool IsEnabled() const;

	/**
	* Returns true if the action has to start after being created. False otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Action")
	bool HasToStartOnCreation() const;

	/**
	* Set the action enabled or disabled.
	*/
	UFUNCTION(BlueprintCallable, Category = "Action")
	void SetEnabled(AActor* Instigator, bool Enabled);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSoftObjectPtr<UTexture2D> ActionIcon;
protected:
	UPROPERTY()
	UGSActionComponent* ActionComp;

	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer GrantsTags;

	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer BlockedTags;

	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer StopActionTags;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName ActionName;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	bool bIsEnabled{true};

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	bool bAutoStart{false};

	bool bIsActive{false};
};
