// Copyright Maxjestic


#include "Core/FTHUD.h"

#include "Blueprint/UserWidget.h"
#include "Core/FTGameInstance.h"
#include "ForbiddenTask/FTLogChannels.h"
#include "Pawns/FTPlayerPawn.h"
#include "UI/FTHUDWidget.h"

void AFTHUD::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetOwningPlayerController();
	if ( !PlayerController )
	{
		FT_LOG_WARNING( "Player Controller is invalid!" )
		return;
	}

	const UFTGameInstance* GameInstance = GetGameInstance<UFTGameInstance>();
	if ( !GameInstance )
	{
		FT_LOG_ERROR( TEXT("Game Instance is invalid!") );
		return;
	}

	HUDWidget = CreateWidget<UFTHUDWidget>( PlayerController, GameInstance->HUDWidgetClass );
	if ( !HUDWidget )
	{
		FT_LOG_ERROR( "Failed to create HUD Widget" )
		return;
	}

	AFTPlayerPawn* PlayerPawn = Cast<AFTPlayerPawn>( PlayerController->GetPawn() );
	if ( !PlayerPawn )
	{
		FT_LOG_ERROR( TEXT("Player Pawn is invalid") )
		return;
	}

	HUDWidget->BindToPlayerDelegates( PlayerPawn );
	HUDWidget->AddToViewport();
}
