#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GSGameInstance.generated.h"

class UGSItemDataLoader;

/**
 * 
 */
UCLASS()
class GS_RPGGAME_API UGSGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGSItemDataLoader> DataLoader;
};
