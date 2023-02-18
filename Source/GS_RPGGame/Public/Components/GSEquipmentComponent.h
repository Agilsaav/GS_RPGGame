#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Gameplay/GameplayTypes.h"
#include "GSEquipmentComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquipmentEquipped, EGSEquipableType, EquipmentType);

class AGSEquipableObject;

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
	AGSEquipableObject* GetEquipment(EGSEquipableType EquipmentType) const;

	/**
	* Set the equipment object
	*/
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void SetEquipment(EGSEquipableType EquipmentType, AGSEquipableObject* NewItem);

	/**
	* Remove the equipment object
	*/
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void RemoveEquipment(EGSEquipableType EquipmentType);

	/**
	* Return the main weapon. If there is no weapon equipped returns nullptr
	*/
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	AGSEquipableObject* GetPrimaryWeapon(EGSEquipableType EquipmentType) const;

	/**
	* Return the main weapon. If there is no weapon equipped returns nullptr
	*/
	UFUNCTION(BlueprintCallable, Category = "Weapons")
	AGSEquipableObject* GetSecondaryWeapon(EGSEquipableType EquipmentType) const;

	/**
	* Return if the slots is equiped.
	*/
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	bool IsSlotEquipped(EGSEquipableType EquipmentType) const;

	/**
	* Return if the main weapon is equipped.
	*/
	UFUNCTION(BlueprintCallable, Category = "Weapons")
	bool HasMainWeapon() const;

	/**
	* Return if the secondary weapon is equipped.
	*/
	UFUNCTION(BlueprintCallable, Category = "Weapons")
	bool HasSecondaryWeapon() const;

	FOnEquipmentEquipped OnEquipmentEquipped, OnEquipmentUnEquipped;

private:
	UPROPERTY()
	TMap<EGSEquipableType, AGSEquipableObject*> Equipment;
};
