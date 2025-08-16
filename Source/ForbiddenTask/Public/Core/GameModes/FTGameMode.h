// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FTGameMode.generated.h"

class AFTBasePawn;

/**
 * Base GameMode class for the ForbiddenTask project.
 * Keeps track of living enemies and Handles Win/Lose conditions
 */
UCLASS()
class FORBIDDENTASK_API AFTGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
    /** Called by the spawner to register a new enemy with the Game Mode. */
	void RegisterEnemy( AFTBasePawn* NewEnemy );

protected:
	//~ Begin AGameModeBase Interface
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
	//~ End AGameModeBase Interface

private:
    /** Callback bound to an enemy OnPawnDied delegate. */
	UFUNCTION()
	void HandleEnemyDied( AFTBasePawn* DeadEnemy );

    /** Callback bound to the player OnPawnDied delegate. */
	UFUNCTION()
	void HandlePlayerDeath( AFTBasePawn* DeadPlayer );

	/**
	 * Triggers the end of the game and handles the win/loss state.
	 * @param bPlayerWon True if the player won, false if they lost.
	 */
	void EndGame( const bool bPlayerWon );

	/** The current count of living enemies, managed by this Game Mode. */
	int32 AliveEnemies = 0;

    /** Flag to prevent EndGame from being called multiple times. */
	bool bIsGameOver = false;
};
