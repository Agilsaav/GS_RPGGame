#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gameplay/GameplayTypes.h"
#include "GSObject.generated.h"


UCLASS()
class GS_RPGGAME_API AGSObject : public AActor
{
	GENERATED_BODY()
	
public:	
	AGSObject() = default; 
	AGSObject(EGSItemType ObjType) : Type(ObjType) {};

	/**
	* Returns the object type
	*/
	UFUNCTION(Category = "C++", BlueprintPure)
	FORCEINLINE EGSItemType GetType() const noexcept { return Type; }

	/**
	* Set the owner of the object
	*/
	void SetOwner(AActor* NewOwner);

	/**
	* Main function for interaction with the object. Do not confuse with InteractableActors.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void InteractWith(APawn* InstigatorPawn);

	EGSItemType Type;
	
protected:
	UPROPERTY()
	AActor* ObjOwner{nullptr};

private:
	
};
