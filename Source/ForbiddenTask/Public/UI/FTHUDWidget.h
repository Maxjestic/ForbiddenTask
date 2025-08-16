// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FTHUDWidget.generated.h"

class AFTPlayerPawn;

/**
 * Base class for the main in-game HUD.
 * Handles the logic for binding to player pawn delegates and provides Blueprint-implementable
 * events for updating the UI's visual elements.
 */
UCLASS()
class FORBIDDENTASK_API UFTHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	 * Initializes the HUD by binding its update functions to the Player Pawn delegates.
	 * @param PlayerPawn The player pawn to get data from.
	 */
	void BindToPlayerDelegates( AFTPlayerPawn* PlayerPawn );

protected:
	/**
	 * Event called when the Strength stat changes. Implement in Blueprint to update the progress bar.
	 * @param NewStrength The new strength value of the player.
	 */
	UFUNCTION( BlueprintimplementableEvent, Category = "HUD" )
	void UpdateStrengthBar( const float NewStrength );
	
	/**
	 * Event called when the Speed stat changes. Implement in Blueprint to update the progress bar.
	 * @param NewSpeed The new speed value of the player.
	 */
	UFUNCTION( BlueprintimplementableEvent, Category = "HUD" )
	void UpdateSpeedBar( const float NewSpeed );

	/** The maximum possible strength value, used to calculate the progress bar percentage. */
	UPROPERTY( BlueprintReadOnly, Category = "HUD" )
	float MaxStrength = 0;

	/** The maximum possible speed value, used to calculate the progress bar percentage. */
	UPROPERTY( BlueprintReadOnly, Category = "HUD" )
	float MaxSpeed = 0;
};
