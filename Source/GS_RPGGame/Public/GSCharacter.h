#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Core/GSAttribute.h"
#include "EnhancedInput/Public/InputActionValue.h"
#include "GSCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UGSActionComponent;
class UInputMappingContext;
class UGSInputDataAsset;

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
protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere, Category = "Components")
	UGSActionComponent* ActionComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UGSInputDataAsset* InputActions;

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

	UFUNCTION()
	void OnHealthChange(const FAttributeChangeDetails& AttributeChangeDetails);
};
