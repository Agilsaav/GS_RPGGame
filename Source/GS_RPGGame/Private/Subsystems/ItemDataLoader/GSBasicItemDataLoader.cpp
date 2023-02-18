#include "Subsystems/ItemDataLoader/GSBasicItemDataLoader.h"
#include "Engine/AssetManager.h"
#include "GSCharacter.h"
#include "DataAssets/UGSObjectDataAsset.h"
#include "Gameplay/GSObject.h"

static constexpr float FORWARD_OFFSET{10.0f};
static constexpr float VERTICAL_OFFSET{60.0f};

void GSBasicItemDataLoader::OnItemDataLoaded(FPrimaryAssetId LoadedId, AActor* ItemOwner, FGSItemDataLoadedContext Context) const
{
	UAssetManager* Manager = UAssetManager::GetIfValid();
	UGSObjectDataAsset* ItemData = Cast<UGSObjectDataAsset>(Manager->GetPrimaryAssetObject(LoadedId));
	if (!ItemData)
	{
		return;
	}

	// TODO: Improve spawn of the object
	AGSCharacter* Character = Cast<AGSCharacter>(ItemOwner);
	const FVector SpawnPosition = Character->GetActorLocation() + 
								  FORWARD_OFFSET * (Character->GetActorForwardVector().Normalize()) + 
								  VERTICAL_OFFSET * (Character->GetActorUpVector().Normalize());
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = Character;

	AGSObject* Item = Character->GetWorld()->SpawnActor<AGSObject>(ItemData->Item, SpawnPosition, Character->GetActorRotation(), SpawnParams);
	Item->InteractWith(Character);
}