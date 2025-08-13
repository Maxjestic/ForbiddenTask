// Fill out your copyright notice in the Description page of Project Settings.

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

	//~ Begin IFTConsumable Interface

	/**
	 * Handles being consumed by the Player
	 * Can be overriden in blueprint
	 * @param PlayerPawn Used for altering player stats
	 */
	virtual void AttemptToConsume_Implementation( AFTPlayerPawn* PlayerPawn ) override;

	//~ End IFTConsumable Interface

protected:
	/**
	 * Stat values that will be added to Player Stats. Can be negative.
	 * They are multiplied by -1.0 if the Player Strength < Enemy Strength.
	 * Unless any value is negative, then Player Strength is not checked
	 * And values are passed without alternation. 
	 */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Stats" )
	float StrengthToGive = 0.f;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Stats" )
	float SpeedToGive = 0.f;
};
