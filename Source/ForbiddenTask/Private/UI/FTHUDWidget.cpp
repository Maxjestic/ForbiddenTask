// Copyright Maxjestic


#include "UI/FTHUDWidget.h"

#include "Pawns/FTPlayerPawn.h"

void UFTHUDWidget::BindToPlayerDelegates( AFTPlayerPawn* PlayerPawn )
{
	PlayerPawn->OnStrengthChanged.AddDynamic( this, &UFTHUDWidget::UpdateStrengthBar );
	PlayerPawn->OnSpeedChanged.AddDynamic( this, &UFTHUDWidget::UpdateSpeedBar );

	MaxStrength = PlayerPawn->GetMaxStrength();
	MaxSpeed = PlayerPawn->GetMaxSpeed();
	UpdateStrengthBar( PlayerPawn->GetStrength() );
	UpdateSpeedBar( PlayerPawn->GetSpeed() );
}
