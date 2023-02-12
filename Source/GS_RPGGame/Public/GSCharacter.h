#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Core/GSAttribute.h"
#include "EnhancedInput/Public/InputActionValue.h"
#include "GameplayTagContainer.h"
#include "GSCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UGSActionComponent;
class UInputMappingContext;
class UGSInputDataAsset;
class UGSInteractionComponent;
class USphereComponent;
class UGSLevelComponent;
class UUserWidget;
class UGSEquipmentComponent;
class UGSInventoryComponent;

UCLASS()
class GS_RPGGAME_API AGSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGSCharacter();

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Called every frame
	void Tick(float DeltaTime) override;

	/**
	* Returns the action component.
	*/
	UFUNCTION(Category = "C++", BlueprintPure) 
	FORCEINLINE UGSActionComponent* GetActionComponent() const noexcept { return ActionComp; }

	/**
	* Returns the interaction component.
	*/
	UFUNCTION(Category = "C++", BlueprintPure)
	FORCEINLINE UGSInteractionComponent* GetInteractionComponent() const noexcept { return InteractionComp; }

	/**
	* Returns the level component.
	*/
	UFUNCTION(Category = "C++", BlueprintPure)
	FORCEINLINE UGSLevelComponent* GetLevelComponent() const noexcept { return LevelComp; }

	/**
	* Returns the level component.
	*/
	UFUNCTION(Category = "C++", BlueprintPure)
	FORCEINLINE UGSEquipmentComponent* GetEquipmentComponent() const noexcept { return EquipmentComp; }

	/**
	* Returns the level component.
	*/
	UFUNCTION(Category = "C++", BlueprintPure)
	FORCEINLINE UGSInventoryComponent* GetInevntoryComponent() const noexcept { return InventoryComp; }

	/**
	* Returns the class name.
	*/
	UFUNCTION(BlueprintCallable, Category = "Class")
	FName GetClassName() const;

	/**
	* Sets the class of the character.
	*/
	void SetClass(FGameplayTag ClassTag);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere, Category = "Components")
	UGSActionComponent* ActionComp;

	UPROPERTY(EditAnywhere, Category = "Components")
	UGSInteractionComponent* InteractionComp;

	UPROPERTY(EditAnywhere, Category = "Components")
	UGSLevelComponent* LevelComp;

	UPROPERTY(EditAnywhere, Category = "Components")
	UGSEquipmentComponent* EquipmentComp;

	UPROPERTY(EditAnywhere, Category = "Components")
	UGSInventoryComponent* InventoryComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UGSInputDataAsset* InputActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Class")
	FGameplayTag Class;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> CharacterWidgetClass;
private:
	// Allow actors to initialize themselves after all of their components have been initialized
	void PostInitializeComponents() override;

	// Called when the game starts or when spawned
	 void BeginPlay() override;

	 // Returns Pawn's eye location
	 FVector GetPawnViewLocation() const override;

	 /**
	 * Moves the character
	 */
	 void Move(const FInputActionValue& Value);

	 /**
	 * Moves the character looking direction
	 */
	 void Look(const FInputActionValue& Value);

	 /**
	 * Call the action to interact
	 */
	 void Interact();

	 /**
	 * 
	 */
	 void OnCharacterHUDPressed();

	 /**
	 * Function called on OnHealthChanged event.
	 */
	UFUNCTION()
	void OnHealthChanged(const FAttributeChangeDetails& AttributeChangeDetails);

	UPROPERTY()
	UUserWidget* CharacterWidgetInstance;

	FAttributeChanged OnHealthChange;
};
