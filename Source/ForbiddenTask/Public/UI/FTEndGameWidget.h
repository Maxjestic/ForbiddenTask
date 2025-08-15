// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FTEndGameWidget.generated.h"

/**
 * Base class for End Game Screen
 * Displays proper Text when the Game Ends
 */
UCLASS()
class FORBIDDENTASK_API UFTEndGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintImplementableEvent )
	void UpdateEndScreenText(const bool bPlayerWon);
};
