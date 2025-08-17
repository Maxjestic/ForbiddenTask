// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/FTConsumable.h"
#include "Pawns/FTBasePawn.h"
#include "FTEnemyPawn.generated.h"

/**
 * AFTEnemyPawn represents an enemy pawn in the game, derived from AFTBasePawn
 * and implementing the IFTConsumable interface.
 *
 * This class defines behavior for enemy pawns that can be "consumed" by player pawns.
 * It contains stats related to the benefits or penalties it provides upon consumption.
 */
UCLASS( Blueprintable )
class FORBIDDENTASK_API AFTEnemyPawn : public AFTBasePawn, public IFTConsumable
{
	GENERATED_BODY()

public:
	/**
	 * Default constructor
	 * Sets Collision Profile
	 */
	AFTEnemyPawn();

	//~ Begin AFTBasePawn Interface
	virtual void SetStats(const float NewStrength, const float NewSpeed) override;
	//~ End AFTBasePawn Interface
	
	//~ Begin IFTConsumable Interface

	/**
	 * Handles being consumed by the Player
	 * MUST be overriden in the Blueprint
	 * Don't call Parent Version
	 * @param PlayerPawn Used for altering player stats
	 */
	virtual void AttemptToConsume_Implementation( AFTPlayerPawn* PlayerPawn ) override;

	//~ End IFTConsumable Interface

protected:
	//~ Begin AActor Interface
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~ End AActor Interface
	
};
