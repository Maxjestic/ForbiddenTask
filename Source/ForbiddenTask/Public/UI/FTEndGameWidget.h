// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FTEndGameWidget.generated.h"

/**
 * Base class for the End Game screen widget.
 * Provides callable event to update the widget's state.
 */
UCLASS()
class FORBIDDENTASK_API UFTEndGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	 * Updates the widget's display based on the game's outcome.
	 * This event is implemented in the child Blueprint.
	 * @param bPlayerWon True if the player won, false if they lost.
	 */
	UFUNCTION( BlueprintImplementableEvent, Category = "End Game" )
	void UpdateEndScreenText( const bool bPlayerWon );
};
