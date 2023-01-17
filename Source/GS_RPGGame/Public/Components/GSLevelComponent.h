#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GSLevelComponent.generated.h"

class UCurveFloat;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLevelChanged, int, newLevel);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GS_RPGGAME_API UGSLevelComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	/**
	* Return the level.
	*/
	UFUNCTION(BlueprintCallable, Category = "Level")
	int GetLevel() const;

	/**
	* Return the level.
	*/
	UFUNCTION(BlueprintCallable, Category = "Level")
	float GetRemainingExpToLevelUp() const;

	/**
	* Adds experience
	*/
	UFUNCTION(BlueprintCallable, Category = "Level")
	void AddExperience(float ExpAmount);

	/**
	* Adds levels
	*/
	UFUNCTION(BlueprintCallable, Category = "Level")
	void AddLevels(float Levels);

	/**
	* Returns wether the current level is the max
	*/
	UFUNCTION(BlueprintCallable, Category = "Level")
	bool IsMaxLevel() const;

	FLevelChanged OnLevelChanged;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Level")
	UCurveFloat* LevelCurve;

private:
	/**
	* Increases the level
	*/
	void LevelUp();

	float CurrentLevelExp{0.f};
	float TotalExp{0.f};
	int CurrentLevel{1};
	int MaxLevel{99};
};
