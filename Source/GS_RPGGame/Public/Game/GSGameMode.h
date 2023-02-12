#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GSGameMode.generated.h"

class UDataTable;
class AGSCharacter;

/**
 * 
 */
UCLASS()
class GS_RPGGAME_API AGSGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	/**
	 * Initialize the game.
	 * The GameMode's InitGame() event is called before any other functions (including PreInitializeComponents() )
	 * and is used by the GameMode to initialize parameters and spawn its helper classes.
	 * @warning: this is called before actors' PreInitializeComponents.
	 */
	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	/** Tries to spawn the player's pawn, at the location returned by FindPlayerStart */
	void RestartPlayer(AController* NewPlayer) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Character")
	UDataTable* CharacterClassesTable;

private:
	/**
	* Initialize the player class
	*/
	void InititalizePlayerClass();

	/**
	* Function called when the Asset Manager finishes to load the character class data
	*/
	void OnCharacterDataLoaded(FPrimaryAssetId LoadedId, AGSCharacter* Character) const;

	bool PlayerInitialized{false};
};
