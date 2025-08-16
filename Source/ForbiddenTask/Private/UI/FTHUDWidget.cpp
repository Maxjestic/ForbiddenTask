// Copyright Maxjestic


#include "UI/FTHUDWidget.h"

#include "ForbiddenTask/FTLogChannels.h"
#include "Pawns/FTPlayerPawn.h"

void UFTHUDWidget::BindToPlayerDelegates( AFTPlayerPawn* PlayerPawn )
{
	if (!PlayerPawn)
	{
		FT_LOG_ERROR(TEXT("Invalid PlayerPawn to bind to!"));
		return;
	}
	
	PlayerPawn->OnStrengthChanged.AddDynamic( this, &UFTHUDWidget::UpdateStrengthBar );
	PlayerPawn->OnSpeedChanged.AddDynamic( this, &UFTHUDWidget::UpdateSpeedBar );

	MaxStrength = PlayerPawn->GetMaxStrength();
	MaxSpeed = PlayerPawn->GetMaxSpeed();
	
	UpdateStrengthBar( PlayerPawn->GetStrength() );
	UpdateSpeedBar( PlayerPawn->GetSpeed() );
}
