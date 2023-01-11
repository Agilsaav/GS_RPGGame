#include "Core/GSAttributeSet.h"
#include "GameplayTagsManager.h"
#include "Components/GSActionComponent.h"
#include "Math/UnrealMathUtility.h"

void UGSAttributeSet::Initialize(UGSActionComponent* NewActionComp)
{
	ActionComp = NewActionComp;
	Health = MaxHealth;
}

bool UGSAttributeSet::ApplyAttributeChange(const FAttributeModification& AttributeMod)
{
	TOptional<FName> AttributeName = GetAttributeName(AttributeMod.AttributeName);
	if (!AttributeName.IsSet())
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find the Attribute with gameplay tag: %s"), *AttributeMod.AttributeName.GetTagName().ToString());
		return false;
	}

	// We use the property system to get the value from the name
	FStructProperty* Property = CastField<FStructProperty>(GetClass()->FindPropertyByName(AttributeName.GetValue()));
	if (Property)
	{
		FAttribute* Attribute = Property->ContainerPtrToValuePtr<FAttribute>(this);
		const FAttribute OldValue = *Attribute;
		switch (AttributeMod.ChangeType)
		{
			case EAttributeChangeType::Add:
				*Attribute = *Attribute + AttributeMod.AttributeValue;
				break;
			
			case EAttributeChangeType::Override:
				*Attribute = AttributeMod.AttributeValue;
				break;
		}

		const bool HasChanged = (*Attribute != OldValue);
		if (HasChanged)
		{
			PostAttributeChange(AttributeMod);

			FAttributeChangeDetails AttributeChangeDetails(ActionComp, AttributeMod.InstigatorComponent.Get(), (*Attribute).GetValue(), OldValue.GetValue(), AttributeMod.AttributeName, AttributeMod.ChangeType);
			Attribute->OnAttributeChanged.Broadcast(AttributeChangeDetails);
		}

		return HasChanged;
	}

	return false;
}

bool UGSAttributeSet::GetAttribute(FGameplayTag AttributeTag, FAttribute& OutAttribute)
{
	TOptional<FName> AttributeName = GetAttributeName(AttributeTag);
	if (!AttributeName.IsSet())
	{
		return false;
	}

	FStructProperty* Property = CastField<FStructProperty>(GetClass()->FindPropertyByName(AttributeName.GetValue()));
	if (!Property)
	{
		return false;
	}

	FAttribute* Attribute = Property->ContainerPtrToValuePtr<FAttribute>(this);
	OutAttribute = *Attribute;

	return true;
}

float UGSAttributeSet::GetAttributeValue(FGameplayTag AttributeTag)
{
	FAttribute Attribute;
	if (GetAttribute(AttributeTag, Attribute))
	{
		return Attribute.GetValue();
	}
	return 0.0f;
}

void UGSAttributeSet::PostAttributeChange(const FAttributeModification& AttributeMod)
{
	// TODO: Find a better way to clamp it without all the if
	static const FGameplayTag HealthTag = UGameplayTagsManager::Get().RequestGameplayTag("Attributes.Health");
	static const FGameplayTag StaminaTag = UGameplayTagsManager::Get().RequestGameplayTag("Attributes.Stamina");
	static const FGameplayTag ManaTag = UGameplayTagsManager::Get().RequestGameplayTag("Attributes.Mana");
	if (AttributeMod.AttributeName == HealthTag)
	{
		Health.Base = FMath::Clamp(Health.Base, 0.0f, MaxHealth.GetValue());
		if (Health.Base == 0.0f)
		{
			//TODO: Dead
		}
	}
	else if (AttributeMod.AttributeName == StaminaTag)
	{
		static const FGameplayTag MaxStaminaTag = UGameplayTagsManager::Get().RequestGameplayTag("Attributes.MaxStamina");
		ClampAttribute(StaminaTag, MaxStaminaTag);
	}
	else if (AttributeMod.AttributeName == ManaTag)
	{
		static const FGameplayTag MaxManaTag = UGameplayTagsManager::Get().RequestGameplayTag("Attributes.MaxStamina");
		ClampAttribute(ManaTag, MaxManaTag);
	}
}

TOptional<FName> UGSAttributeSet::GetAttributeName(FGameplayTag AttributeTag) const
{
	if (!AttributeTag.IsValid())
	{
		return TOptional<FName>();
	}
	
	// Attribute tag should be: Attribute.AttributeName (Ex: Attribute.Health)
	const FName TagName = AttributeTag.GetTagName();
	FString AttributePrefix, AttributeName;
	TagName.ToString().Split(".", &AttributePrefix, &AttributeName, ESearchCase::IgnoreCase, ESearchDir::FromEnd);

	return AttributeName.IsEmpty() ? TOptional<FName>() : TOptional<FName>(FName(*AttributeName));
}

void UGSAttributeSet::ClampAttribute(FGameplayTag AttributeTag, FGameplayTag MaxAttributeTag)
{
	FAttribute Attribute, MaxAttribute;
	if (GetAttribute(AttributeTag, Attribute) && GetAttribute(MaxAttributeTag, MaxAttribute))
	{
		Attribute.Base = FMath::Clamp(Attribute.Base, 0.0f, MaxAttribute.GetValue());
	}
}

UGSActionComponent* UGSAttributeSet::GetOwningComponent() const
{
	return ActionComp;
}
