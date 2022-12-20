#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GSCharacter.generated.h"

class UGSActionComponent;

UCLASS()
class GS_RPGGAME_API AGSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGSCharacter();

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Components")
	UGSActionComponent* ActionComp;

private:
	// Called when the game starts or when spawned
	 void BeginPlay() override;
};
