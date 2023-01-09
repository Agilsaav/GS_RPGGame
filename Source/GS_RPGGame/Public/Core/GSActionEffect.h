#pragma once

#include "CoreMinimal.h"
#include "Core/GSAction.h"
#include "GSActionEffect.generated.h"

/**
 * Actions with duration fixed and/or applied with some frequency. (Ex: Buff and Debuff).
 */
UCLASS()
class GS_RPGGAME_API UGSActionEffect : public UGSAction
{
	GENERATED_BODY()

public:	
	UGSActionEffect();

	/**
	* Starts the action Implementation
	*/
	void StartAction_Implementation(AActor* Instigator) override;

	/**
	* Stops the action Implementation
	*/
	void StopAction_Implementation(AActor* Instigator) override;

	/**
	* Returns the time remaining until it finishes.
	*/
	UFUNCTION(BlueprintCallable, Category = "ActionEffect")
	float GetTimeRemaining() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSoftObjectPtr<UTexture2D> EffectIcon;
protected:
	/**
	* Executes the effect. This function has to be implemented by childs(C++ or BP).
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "ActionEffect")
	void ExecutePeriodicEffect(AActor* Instigator);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ActionEffect")
	float Duration{30.0f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ActionEffect")
	float Period{1.0f};

private:
	FTimerHandle DurationHandle;
	FTimerHandle PeriodHandle;
	float TimeStarted;
};
