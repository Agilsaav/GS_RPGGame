#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GSActionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GS_RPGGAME_API UGSActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGSActionComponent();

private:
	// Called when the game starts
	void BeginPlay() override;
};
