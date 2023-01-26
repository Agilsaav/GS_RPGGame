#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GSAttribute.h"
#include "Misc/Optional.h"
#include "GSAttributeSet.generated.h"

class UGSActionComponent;

/**
 * 
 */
UCLASS(Blueprintable)
class GS_RPGGAME_API UGSAttributeSet : public UObject
{
	GENERATED_BODY()
public:
	/**
	* Inititalize the object.
	*/
	void Initialize(UGSActionComponent* NewActionComp);

	/**
	* Applies a change to an existing attribute. Return true if the attribute changes, false otherwise.
	*/
	UFUNCTION(BlueprintCallable)
	bool ApplyAttributeChange(const FAttributeModification& AttributeMod);

	/**
	* Returns true if the attribute is found, and the parameter OutAttribute is the desired attribute.
	* DO NOT USE TO CHANGE THE ATTRIBUTE.
	*/
	UFUNCTION(BlueprintCallable)
	bool GetAttribute(FGameplayTag AttributeTag, FAttribute& OutAttribute);

	/**
	* Returns the value of an attribute. If the attribute does not exist returns 0.
	*/
	UFUNCTION(BlueprintCallable)
	float GetAttributeValue(FGameplayTag AttributeTag);

	/**
	* Resets the Attribute to defaults setting with a new Base value.
	*/
	UFUNCTION(BlueprintCallable)
	void ResetAttributeValueByName(float NewValue, FName AttributeName);

	/**
	* Resets the Attribute to defaults setting with a new Base value.
	*/
	UFUNCTION(BlueprintCallable)
	void ResetAttributeValue(float NewValue, FGameplayTag AttributeTag);

	/**
	* Returns the owning component.
	*/
	UFUNCTION(BlueprintCallable, Category = "Action")
	UGSActionComponent* GetOwningComponent() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	FAttribute Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	FAttribute MaxHealth {100.0f};

private:
	/**
	* Apply rules reacting from a change made to an attribute can be override.
	*/
	virtual void PostAttributeChange(const FAttributeModification& AttributeMod);

	/**
	* Search the attribute name using the gameplay tag.
	* Returns the attribute name if it is found , otherwise returns a non set optional object.
	*/
	TOptional<FName> GetAttributeName(FGameplayTag AttributeTag) const;

	/**
	* Clamps an attribute given a max attribute.
	*/
	void ClampAttribute(FGameplayTag AttributeTag, FGameplayTag MaxAttributeTag);

	UPROPERTY()
	UGSActionComponent* ActionComp;
};
