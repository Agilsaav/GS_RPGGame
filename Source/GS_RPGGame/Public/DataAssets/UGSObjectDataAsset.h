#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "Core/GSAttribute.h"
#include "Gameplay/GameplayTypes.h"
#include "UGSObjectDataAsset.generated.h"

class AGSObject;
class UGSAction;


/**
 * Data Asset for the initialization of the Character
 */
UCLASS()
class GS_RPGGAME_API UGSObjectDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId("ItemClass", GetFName()); };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TSubclassOf<AGSObject> Item;
};

/**
 * Data Asset for the initialization of the Character
 */
UCLASS()
class GS_RPGGAME_API UGSEquipableDataAsset : public UGSObjectDataAsset
{
	GENERATED_BODY()

public:
	FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId("EquipableItemClass", GetFName()); };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	EGSEquipableType Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FName SocketName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	TArray<FAttributeModification> AttributesMods;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TMap<FGameplayTag, TSubclassOf<UGSAction>> ActiveActions;
};
