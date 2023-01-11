#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnhancedInput/Public/InputAction.h"
#include "GSInputDataAsset.generated.h"

/**
 * Stores the input actions for the character
 */
UCLASS()
class GS_RPGGAME_API UGSInputDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputMove;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputLook;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputInteraction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)    
    UInputAction* InputSpace;
};
