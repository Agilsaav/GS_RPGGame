#include "GSCharacter.h"
#include "Components/GSActionComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayTagsManager.h"
#include "Core/GSAttributeSet.h"
#include "DataAssets/GSInputDataAsset.h"

#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/InputMappingContext.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "EnhancedInput/Public/InputActionValue.h"

AGSCharacter::AGSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateAbstractDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 100.0f;

	CameraComp = CreateAbstractDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComp->SetupAttachment(SpringArmComp);

	ActionComp = CreateAbstractDefaultSubobject<UGSActionComponent>("ActionComponent");

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate the arm based on the controller
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	SpringArmComp->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraComp->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void AGSCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGSCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (ActionComp->AttributesSet)
	{
		// TODO: ActionComp->AddAttributeListener(HealthTag, this,  &AGSCharacter::OnHealthChange)
		static const FGameplayTag HealthTag = UGameplayTagsManager::Get().RequestGameplayTag("Attributes.Health");
		ActionComp->AttributesSet->Health.OnAttributeChanged.AddDynamic(this, &AGSCharacter::OnHealthChange);
	}
}

void AGSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector AGSCharacter::GetPawnViewLocation() const
{
	return CameraComp->GetComponentLocation();
}

void AGSCharacter::OnHealthChange(const FAttributeChangeDetails& AttributeChangeDetails)
{

}

void AGSCharacter::Move(const FInputActionValue& Value)
{
	if (Controller)
	{
		const FVector2D MoveValue = Value.Get<FVector2D>();
		const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);

		if (MoveValue.Y != 0.f)
		{
			const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);
			AddMovementInput(Direction, MoveValue.Y);
		}

		if (MoveValue.X != 0.f)
		{
			const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);
			AddMovementInput(Direction, MoveValue.X);
		}
	}
}

void AGSCharacter::Look(const FInputActionValue& Value)
{
	if (Controller)
	{
		const FVector2D LookValue = Value.Get<FVector2D>();
		AddControllerYawInput(LookValue.X);
		AddControllerPitchInput(LookValue.Y);
	}
}

void AGSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PController = Cast<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PController->GetLocalPlayer());

	EnhancedInputSubsystem->ClearAllMappings();
	EnhancedInputSubsystem->AddMappingContext(InputMapping, 0);

	if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComp->BindAction(InputActions->InputMove, ETriggerEvent::Triggered, this, &AGSCharacter::Move);
		EnhancedInputComp->BindAction(InputActions->InputLook, ETriggerEvent::Triggered, this, &AGSCharacter::Look);
		EnhancedInputComp->BindAction(InputActions->InputSpace, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		//EnhancedInputComp->BindAction(InputActions->InputInteraction, ETriggerEvent::Triggered, this, &AGSCharacter::Look);
	}
}

