#include "Game/GSGameMode.h"
#include "DataAssets/GSInitialCharacterDataAsset.h"
#include "GSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/AssetManager.h"
#include "Components/GSActionComponent.h"
#include "Components/GSLevelComponent.h"
#include "Components/GSInventoryComponent.h"
#include "Components/GSEquipmentComponent.h"
#include "Core/GSAttributeSet.h"
#include "GameplayTagsManager.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/GSItemDataLoader.h"
#include "Gameplay/GameplayTypes.h"

static constexpr int MINIMUM_LEVEL{1};

void AGSGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	// TODO: Add Load Game when implemnented instead of creating a new character

	//We cannot load Character information because here the PC and PPawn are not created. Player Pawn is not created until the Restart Player
}

void AGSGameMode::RestartPlayer(AController* NewPlayer)
{
	Super::RestartPlayer(NewPlayer);

	// I do not like that the initialization of the character is here. Find a better place if there is one!
	// + In the future add load character data in save.
	if (!PlayerInitialized)
	{
		InititalizePlayerClass();
	}
}

void AGSGameMode::InititalizePlayerClass()
{
	AGSCharacter* Character = Cast<AGSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	FGSInitialCharacterInfoRow* ClassRow = CharacterClassesTable->FindRow<FGSInitialCharacterInfoRow>(Character->GetClassName(), "CharacterClass");

	if (ClassRow)
	{
		UAssetManager* Manager = UAssetManager::GetIfValid();

		TArray<FName> Bundles;
		FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(this, &AGSGameMode::OnCharacterDataLoaded, ClassRow->CharacterClassData, Character);
		Manager->LoadPrimaryAsset(ClassRow->CharacterClassData, Bundles, Delegate);

		Character->GetLevelComponent()->AddLevels(ClassRow->Level - MINIMUM_LEVEL);

		// I do not like this, maybe in the future find another way to do it. Maybe insted of having a float have a pairt tag,float
		UGSAttributeSet* AttributeSet = Character->GetActionComponent()->AttributesSet;
		AttributeSet->ResetAttributeValue(ClassRow->Health, UGameplayTagsManager::Get().RequestGameplayTag("Attributes.MaxHealth"));
		AttributeSet->ResetAttributeValue(ClassRow->Mana, UGameplayTagsManager::Get().RequestGameplayTag("Attributes.MaxMana"));
		AttributeSet->ResetAttributeValue(ClassRow->Mana, UGameplayTagsManager::Get().RequestGameplayTag("Attributes.Mana"));
		AttributeSet->ResetAttributeValue(ClassRow->Stamina, UGameplayTagsManager::Get().RequestGameplayTag("Attributes.MaxStamina"));
		AttributeSet->ResetAttributeValue(ClassRow->Stamina, UGameplayTagsManager::Get().RequestGameplayTag("Attributes.Stamina"));
		AttributeSet->ResetAttributeValue(ClassRow->Strenght, UGameplayTagsManager::Get().RequestGameplayTag("Attributes.Strenght"));
		AttributeSet->ResetAttributeValue(ClassRow->Intelligence, UGameplayTagsManager::Get().RequestGameplayTag("Attributes.Intelligence"));
		AttributeSet->ResetAttributeValue(ClassRow->Dexterity, UGameplayTagsManager::Get().RequestGameplayTag("Attributes.Dexterity"));
		AttributeSet->ResetAttributeValue(ClassRow->Crit, UGameplayTagsManager::Get().RequestGameplayTag("Attributes.Crit"));
		AttributeSet->ResetAttributeValue(ClassRow->Armor, UGameplayTagsManager::Get().RequestGameplayTag("Attributes.Armor"));
		AttributeSet->ResetAttributeValue(ClassRow->MagicResistance, UGameplayTagsManager::Get().RequestGameplayTag("Attributes.MagicResistance"));

		PlayerInitialized = true;
	}
}

void AGSGameMode::OnCharacterDataLoaded(FPrimaryAssetId LoadedId, AGSCharacter* Character) const
{
	UAssetManager* Manager = UAssetManager::GetIfValid();
	UGSInitialCharacterDataAsset* CharacterData = Cast<UGSInitialCharacterDataAsset>(Manager->GetPrimaryAssetObject(LoadedId));
	if (!CharacterData)
	{
		return;
	}

	UGSActionComponent* ActionComp = Character->GetActionComponent();
	if (ActionComp)
	{
		for (const auto& [ActionTag, Action] : CharacterData->Actions)
		{
			ActionComp->AddAction(Character, ActionTag, Action);
		}
	}

	UGSInventoryComponent* InventoryComp = Character->GetInevntoryComponent();
	for (const auto& [Name, ItemType] : CharacterData->Items)
	{
		InventoryComp->AddItem(Name, ItemType);
	}

	UGSEquipmentComponent* EquipmentComp = Character->GetEquipmentComponent();
	for (const auto& [Name, EquipmentType] : CharacterData->Equipment)
	{
		InventoryComp->AddItem(Name, EGSItemType::Armor);

		UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		UGSItemDataLoader* DataLoader = GameInstance->GetSubsystem<UGSItemDataLoader>();
		FGSItemData EquipmentToLoad = InventoryComp->GetItemData(Name, EGSItemType::Armor);
		DataLoader->LoadEquipment(EquipmentToLoad.ItemClassData, Character, EquipmentType);
	}

	for (const auto& [Name, EquipmentType] : CharacterData->Weapons)
	{
		InventoryComp->AddItem(Name, EGSItemType::Weapon);
	}
}