#include "Subsystems/ItemDataLoader/GSEquipmentDataLoader.h"
#include "GSCharacter.h"
#include "Components/GSActionComponent.h"
#include "DataAssets/UGSObjectDataAsset.h"
#include "Core/GSAttributesChangeAction.h"
#include "Gameplay/GSEquipableObject.h"
#include "Components/GSEquipmentComponent.h"
#include "Engine/AssetManager.h"

void GSEquipmentDataLoader::OnItemDataLoaded(FPrimaryAssetId LoadedId, AActor* ItemOwner, FGSItemDataLoadedContext Context) const
{
	UAssetManager* Manager = UAssetManager::GetIfValid();
	UGSEquipableDataAsset* EquipmentData = Cast<UGSEquipableDataAsset>(Manager->GetPrimaryAssetObject(LoadedId));
	if (!EquipmentData)
	{
		return;
	}

	AGSCharacter* Character = Cast<AGSCharacter>(ItemOwner);
	const FTransform SocketTransform = Character->GetMesh()->GetSocketTransform(EquipmentData->SocketName);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = Character;

	AGSEquipableObject* Equipment = Character->GetWorld()->SpawnActor<AGSEquipableObject>(EquipmentData->Item, SocketTransform, SpawnParams);
	Equipment->SetOwner(ItemOwner);
	Equipment->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, EquipmentData->SocketName);

	UGSAttributesChangeAction* AttributesChangeAction = NewObject<UGSAttributesChangeAction>(ItemOwner, UGSAttributesChangeAction::StaticClass());
	AttributesChangeAction->CreateAttributesModifications(EquipmentData->AttributesMods);

	Equipment->Initialize(AttributesChangeAction, EquipmentData->ActiveActions);
	Equipment->EquipmentType = Context.EquipmentType;
	Equipment->Type = EGSItemType::Armor;

	//Maybe move this to the inventory and have the pointer of the obj in the inventory
	UGSEquipmentComponent* EquipmentComp = Character->GetEquipmentComponent();
	EquipmentComp->SetEquipment(Context.EquipmentType, Equipment);
}