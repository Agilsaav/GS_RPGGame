#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "GSInitialCharacterDataAsset.generated.h"

class UGSAction;

/**
 * Data Asset for the initialization of the Character 
 */
UCLASS()
class GS_RPGGAME_API UGSInitialCharacterDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId("CharacterClass", GetFName()); };
	
	// TODO: Equipment and weapons

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TMap<FGameplayTag, TSubclassOf<UGSAction>> Actions;
};

/**
 * Data row for the creation of the Character
 */
USTRUCT(BlueprintType)
struct FGSInitialCharacterInfoRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag Class;

	// NOTE: To use FPrimaryAssetId you need to configure it in the Asset Manager (Project Settings)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPrimaryAssetId CharacterClassData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Level{1};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Health{100.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Mana{100.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Stamina{100.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Strenght{10.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Intelligence{10.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Dexterity{10.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Crit{10.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Armor{10.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MagicResistance{10.0f};
};
