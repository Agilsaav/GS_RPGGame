#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "GameplayTagsManager.h"
#include "GameplayTypes.generated.h"

/**
* Different types of items
*/
UENUM(BlueprintType)
enum class EGSItemType : uint8
{
	Usable,
	Weapon,
	Armor,
	Resource,
	Food,
	Others,
	KeyItem
};

/**
* Different types of equipment
*/
UENUM(BlueprintType)
enum class EGSEquipableType : uint8
{
	Head,
	Hands,
	Chest,
	Legs,
	Feet,
	PrimaryAccesory,
	SecondaryAccesory,
	RightHand,	// PrimaryWeapon
	LeftHand	// SecondaryWeapon
};

static const TMap<EGSEquipableType, FGameplayTag> GSEquipableTags = { 
	{EGSEquipableType::Head, UGameplayTagsManager::Get().RequestGameplayTag("Actions.Equipment.Head")},
	{EGSEquipableType::Hands, UGameplayTagsManager::Get().RequestGameplayTag("Actions.Equipment.Hands")},
	{EGSEquipableType::Chest, UGameplayTagsManager::Get().RequestGameplayTag("Actions.Equipment.Chest")},
	{EGSEquipableType::Legs, UGameplayTagsManager::Get().RequestGameplayTag("Actions.Equipment.Legs")},
	{EGSEquipableType::Feet, UGameplayTagsManager::Get().RequestGameplayTag("Actions.Equipment.Feet")},
	{EGSEquipableType::PrimaryAccesory, UGameplayTagsManager::Get().RequestGameplayTag("Actions.Equipment.PrimaryAccesory")},
	{EGSEquipableType::SecondaryAccesory, UGameplayTagsManager::Get().RequestGameplayTag("Actions.Equipment.SecondaryAccesory")},
	{EGSEquipableType::RightHand, UGameplayTagsManager::Get().RequestGameplayTag("Actions.Equipment.RightHand")},
	{EGSEquipableType::LeftHand, UGameplayTagsManager::Get().RequestGameplayTag("Actions.Equipment.LeftHand")},
};

/**
* Struct used to pass data to the loading function
*/
USTRUCT()
struct FGSItemDataLoadedContext
{
	GENERATED_BODY()

	EGSItemType ItemType;
	EGSEquipableType EquipmentType;
};

/**
* Data for an item
*/
USTRUCT(BlueprintType)
struct FGSItemData
{
	GENERATED_BODY()

	FName Id;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	EGSItemType Type {EGSItemType::Others};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPrimaryAssetId ItemClassData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSoftObjectPtr<UTexture2D> UIIcon;
};

/**
* Data for an stackable item
*/
struct FGSStackableItemData
{
	FGSStackableItemData() = default;
	FGSStackableItemData(FGSItemData Data) : ItemData(MoveTemp(Data)) {};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FGSItemData ItemData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	uint32 Stacks {1};
};


/**
 * Data row for the creation of the Character
 */
USTRUCT(BlueprintType)
struct FGSItemRowInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FName Id;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FGSItemData ItemData;
};