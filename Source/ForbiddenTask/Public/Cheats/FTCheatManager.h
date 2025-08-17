// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "FTCheatManager.generated.h"

class AFTPlayerPawn;

/**
 * Custom Cheat Manager for the Forbidden Task project.
 * Provides console commands for debugging and testing gameplay systems.
 */
UCLASS()
class FORBIDDENTASK_API UFTCheatManager : public UCheatManager
{
	GENERATED_BODY()

public:
	//~ Begin UCheatManager Interface
	virtual void God() override;
	//~ End UCheatManager Interface

	// --- Cheats ---

	/** Kills the player, triggering the loss condition. */
	UFUNCTION( Exec, meta = (Help = "Kills all enemies. Results in Lose.") )
	void KillPlayer();

	/** Destroys all living enemies, triggering the win condition. */
	UFUNCTION( Exec, meta = (Help = "Kills all enemies. Results in Win.") )
	void KillAllEnemies() const;

	/** Toggles the freeze state of all enemies. */
	UFUNCTION( Exec, meta = (Help = "Toggles the frozen state for all enemies. Stops/restarts their BT.") )
	void ToggleFreezeEnemies();

	/** Sets the player's current strength and speed to specific values. */
	UFUNCTION( Exec, meta = (Help = "Sets the player's stats. Usage: SetPlayerStats [NewStrength] [NewSpeed]") )
	void SetPlayerStats( const float NewStrength, const float NewSpeed );

	/** Alters the player's stats by the given delta values. */
	UFUNCTION( Exec, meta = (Help = "Alters the player's stats. Usage: SetPlayerStats [NewStrength] [NewSpeed]") )
	void AlterPlayerStats( const float StrengthDelta, const float SpeedDelta );

private:
	/** Gets a cached reference to the player pawn for efficiency. */
	AFTPlayerPawn* GetCachedPlayerPawn();

	UPROPERTY()
	TObjectPtr<AFTPlayerPawn> CachedPlayerPawn = nullptr;

	/** Tracks the current frozen state for the toggle function. */
	bool bAreEnemiesFrozen = false;
};
