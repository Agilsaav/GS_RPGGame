#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Gameplay/GameplayTypes.h"
#include "GSEquipmentComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquipmentEquipped, EGSEquipableType, EquipmentType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GS_RPGGAME_API UGSEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGSEquipmentComponent();
		
	/**
	* Returns a pointer to an equipment object
	*/
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	AActor* GetEquipment(EGSEquipableType EquipmentType) const;

	/**
	* Set the equipment object
	*/
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void SetEquipment(EGSEquipableType EquipmentType, AActor* NewItem);

	/**
	* Remove the equipment object
	*/
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void RemoveEquipment(EGSEquipableType EquipmentType);

	/**
	* Return if the slots is equiped. 
	*/
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	bool IsSlotEquipped(EGSEquipableType EquipmentType) const;

	FOnEquipmentEquipped OnEquipmentEquipped, OnEquipmentUnEquipped;

private:
	UPROPERTY()
	TMap<EGSEquipableType, AActor*> Equipment;
};
