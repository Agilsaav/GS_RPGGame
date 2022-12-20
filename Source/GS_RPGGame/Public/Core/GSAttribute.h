#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GSAttribute.generated.h"

class UGSActionComponent;

USTRUCT(BlueprintType)
struct FAttribute
{
	GENERATED_BODY();

	FAttribute() = default;
	FAttribute(float Value) : Base(Value) {};

	float GetValue() const noexcept { return (Base + Delta) * Multiplier; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Base{10.0f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Delta{0.0f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Multiplier{1.0f};
};

UENUM(BlueprintType)
enum class EAttributeChangeType : uint8
{
	Override,
	Add
};

USTRUCT(BlueprintType)
struct FAttributeModification
{
	GENERATED_BODY();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag AttributeName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EAttributeChangeType ChangeType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FAttribute AttributeChange;

	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<UGSActionComponent> InstigatorComponent;
};