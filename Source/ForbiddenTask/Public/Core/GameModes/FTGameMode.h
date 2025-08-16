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
	/** Called when Enemy gets spawned used to bind callback to OnDeath */
	void RegisterEnemy( AFTBasePawn* NewEnemy );

protected:
	//~ Begin AGameModeBase Interface
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
	//~ End AGameModeBase Interface

private:
	/** Callback for (Enemy) OnPawnDied Delegate */
	UFUNCTION()
	void HandleEnemyDied( AFTBasePawn* DeadEnemy );

	/** Callback for (Player) OnPawnDied Delegate */
	UFUNCTION()
	void HandlePlayerDeath( AFTBasePawn* DeadPlayer );

	/**
	 * Handle End of the game
	 * @param bPlayerWon Information if the Player won or lost
	 */
	void EndGame( const bool bPlayerWon );

	int32 AliveEnemies = 0;

	/** To prevent multiple calls of EndGame */
	bool bIsGameOver = false;
};
