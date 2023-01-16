#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GSWorldWidgetWidget.generated.h"

class USizeBox;

/**
 * Widget to be placed in the world
 */
UCLASS()
class GS_RPGGAME_API UGSWorldWidgetWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "AI", meta = (ExposeOnSpawn = true))
	AActor* AttachedActor;

protected:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Position")
	FVector WorldOffset;

	UPROPERTY(meta = (BindWidget))
	USizeBox* ParentSizeBox;	// We must create a sizebox in the widget named ParentSizeBox!
};
