#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Core/GSAttribute.h"
#include "GSAttribute.generated.h"

class UGSActionComponent;

UENUM(BlueprintType)
enum class EAttributeChangeType : uint8
{
	None,
	Override,
	Add
};

/**
* Struct used to notify a change in an existing attribute
*/
USTRUCT(BlueprintType)
struct FAttributeChangeDetails
{
	GENERATED_BODY();

	FAttributeChangeDetails() = default;

	FAttributeChangeDetails(UGSActionComponent* OwnerComponent, UGSActionComponent* InstigatorComponent, float New, float Old, FGameplayTag Tag, EAttributeChangeType Change) :
		OwnerComp(OwnerComponent), InstigatorComp(InstigatorComponent), NewValue(New), OldValue(Old), AttributeTag(Tag), ChangeType(Change) {};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UGSActionComponent* OwnerComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UGSActionComponent* InstigatorComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float NewValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float OldValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag AttributeTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EAttributeChangeType ChangeType {EAttributeChangeType::Add};
};

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeChanged, const FAttributeChangeDetails&, AttributeChangeDetails);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAttributeChanged, const FAttributeChangeDetails&, AttributeChangeDetails);

/**
* NOTE: Delagetas in structs do not work properly and can't be called in BP.
* If the function AddAttributeListner does not properly work, I can change FAttribute to a class deriving from UObject.
* This will allow me to have the delegate inside the attribute.
*/

USTRUCT(BlueprintType)
struct FAttribute
{
	GENERATED_BODY();

	FAttribute() = default;
	FAttribute(float Value) : Base(Value) {};

	float GetValue() const noexcept { return (Base + Delta) * Multiplier; }

	FAttribute& operator+(const FAttribute& Other)
	{
		Base +=  Other.Base;
		Delta += Other.Delta;
		Multiplier += Other.Multiplier;

		if (bClampToZero)
		{
			Base = FMath::Max(Base, 0.0f);
			Delta = FMath::Max(Delta, 0.0f);
		}

		return *this;
	}

	FAttribute& operator*=(float Scalar)
	{
		Base *= Scalar;
		Delta *= Scalar;
		Multiplier *= Scalar;
		return *this;
	}

	bool operator!=(const FAttribute& Other)
	{
		return (Base != Other.Base) || (Delta != Other.Delta) || (Multiplier != Other.Multiplier);
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Base{10.0f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Delta{0.0f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Multiplier{1.0f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bClampToZero{false};

	//UPROPERTY(BlueprintAssignable)
	//FAttributeChanged OnAttributeChanged;
};

/**
* Struct used to apply a modification to an existing attribute
*/
USTRUCT(BlueprintType)
struct FAttributeModification
{
	GENERATED_BODY();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag AttributeName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EAttributeChangeType ChangeType{EAttributeChangeType::Add};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FAttribute AttributeValue;

	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<UGSActionComponent> InstigatorComponent;
};