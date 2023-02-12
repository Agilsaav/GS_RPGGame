#pragma once

#include "CoreMinimal.h"
#include "Gameplay/GSObject.h"
#include "Gameplay/GSEquipable.h"
#include "GameplayTagContainer.h"
#include "GSEquipableObject.generated.h"

class UGSAttributesChangeAction;
class UGSAction;

/**
 * 
 */
UCLASS()
class GS_RPGGAME_API AGSEquipableObject : public AGSObject, public IGSEquipable
{
	GENERATED_BODY()
	
public:
	/**
	* Initialize the object
	*/
	void Initialize(UGSAttributesChangeAction* NewAttributesChangeAction, TMap<FGameplayTag, TSubclassOf<UGSAction>> NewActiveActions);

	/**
	* Main function for equipping an object.
	*/
	void Equip_Implementation(APawn* InstigatorPawn);

	/**
	* Main function for equipping an object.
	*/
	void UnEquip_Implementation(APawn* InstigatorPawn);

	/**
	* Main function for interaction with the object. Do not confuse with InteractableActors.
	*/
	void InteractWith_Implementatio(APawn* InstigatorPawn);

	/**
	* Returns the description text
	*/
	UFUNCTION(Category = "C++", BlueprintPure)
	FORCEINLINE bool IsEquipped() const { return bIsEquipped; }

	EGSEquipableType EquipmentType;

private:
	UPROPERTY()
	UGSAttributesChangeAction* AttributesChangeAction;

	UPROPERTY()
	TMap<FGameplayTag, TSubclassOf<UGSAction>> ActiveActions;

	bool bIsEquipped{false};
};
