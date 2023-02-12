#include "Subsystems/GSItemDataLoader.h"
#include "Engine/AssetManager.h"
#include "GSCharacter.h"
#include "Components/GSActionComponent.h"
#include "DataAssets/UGSObjectDataAsset.h"
#include "Core/GSAttributesChangeAction.h"
#include "Gameplay/GSEquipableObject.h"
#include "Components/GSEquipmentComponent.h"

bool UGSItemDataLoader::ShouldCreateSubsystem(UObject* Outer) const
{
	if (this->GetClass()->IsInBlueprint()) 
	{
		return true; 
	}

	return false;
}

FGSItemData UGSItemDataLoader::LoadItem(FName ItemId, EGSItemType ItemType) const
{
	FGSItemRowInfo* ItemRow = ItemsData[ItemType]->FindRow<FGSItemRowInfo>(ItemId, "Item");

	if (ItemRow)
	{
		ItemRow->ItemData.Id = ItemId;
		return ItemRow->ItemData;
	}
	return FGSItemData{};
}

void UGSItemDataLoader::LoadEquipment(FPrimaryAssetId EquipmentClassData, AActor* EquipmentOwner, EGSEquipableType EquipmentType)
{
	UAssetManager* Manager = UAssetManager::GetIfValid();

	TArray<FName> Bundles;
	FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(this, &UGSItemDataLoader::OnEquipmentDataLoaded, EquipmentClassData, EquipmentOwner, EquipmentType);
	Manager->LoadPrimaryAsset(EquipmentClassData, Bundles, Delegate);
}

void UGSItemDataLoader::OnEquipmentDataLoaded(FPrimaryAssetId LoadedId, AActor* EquipmentOwner, EGSEquipableType EquipmentType) const
{
	UAssetManager* Manager = UAssetManager::GetIfValid();
	UGSEquipableDataAsset* EquipmentData = Cast<UGSEquipableDataAsset>(Manager->GetPrimaryAssetObject(LoadedId));
	if (!EquipmentData)
	{
		return;
	}

	AGSCharacter* Character = Cast<AGSCharacter>(EquipmentOwner);
	const FTransform SocketTransform = Character->GetMesh()->GetSocketTransform(EquipmentData->SocketName);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = Character;
	
	AGSEquipableObject* Equipment = GetWorld()->SpawnActor<AGSEquipableObject>(EquipmentData->Item, SocketTransform, SpawnParams);
	Equipment->SetOwner(EquipmentOwner);

	UGSAttributesChangeAction* AttributesChangeAction = NewObject<UGSAttributesChangeAction>(EquipmentOwner, UGSAttributesChangeAction::StaticClass());
	AttributesChangeAction->CreateAttributesModifications(EquipmentData->AttributesMods);

	Equipment->Initialize(AttributesChangeAction, EquipmentData->ActiveActions);
	Equipment->EquipmentType = EquipmentType;
	Equipment->Type = EGSItemType::Armor;

	//Maybe move this to the inventory and have the pointer of the obj in the inventory
	UGSEquipmentComponent* EquipmentComp = Character->GetEquipmentComponent();
	EquipmentComp->SetEquipment(EquipmentType, Equipment);

	OnEquipmentLoaded.Broadcast(Equipment->EquipmentType);
}