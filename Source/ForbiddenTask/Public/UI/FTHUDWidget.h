// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FTHUDWidget.generated.h"

class AFTPlayerPawn;
/**
 * Base class for in-game HUD
 * Binds callbacks to the Player delegates
 * Should be implemented in the Blueprint
 */
UCLASS()
class FORBIDDENTASK_API UFTHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindToPlayerDelegates( AFTPlayerPawn* PlayerPawn );

protected:
	UFUNCTION( BLueprintimplementableEvent )
	void UpdateStrengthBar( const float NewStrength );

	UFUNCTION( BLueprintimplementableEvent )
	void UpdateSpeedBar( const float NewSpeed );

	UPROPERTY( BlueprintReadOnly )
	float MaxStrength = 0;
	
	UPROPERTY( BlueprintReadOnly )
	float MaxSpeed = 0;
};
