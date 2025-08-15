// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/FTPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Core/FTGameInstance.h"
#include "ForbiddenTask/FTLogChannels.h"
#include "Pawns/FTPlayerPawn.h"
#include "UI/FTEndGameWidget.h"
#include "UI/FTHUDWidget.h"

void AFTPlayerController::ShowEndScreen( const bool bPlayerWon )
{
	if ( UFTEndGameWidget* EndScreenWidget = CreateWidget<UFTEndGameWidget>(
		this,
		GetGameInstance()->EndScreenWidgetClass ) )
	{
		EndScreenWidget->UpdateEndScreenText( bPlayerWon );
		EndScreenWidget->AddToViewport();
		SetPause( true );

		SetInputMode( FInputModeUIOnly() );
	}
}

void AFTPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if ( UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>( GetLocalPlayer() ) )
	{
		InputSubsystem->AddMappingContext( DefaultInputMappingContext, 0 );
	}
	bShowMouseCursor = true;
}

void AFTPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if ( UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>( InputComponent ) )
	{
		EnhancedInput->BindAction( MoveAction, ETriggerEvent::Triggered, this, &AFTPlayerController::OnMoveTriggered );
		EnhancedInput->BindAction( PauseAction, ETriggerEvent::Triggered, this, &AFTPlayerController::OnPause );
	}
}

void AFTPlayerController::OnPossess( APawn* InPawn )
{
	Super::OnPossess( InPawn );
	ControlledPawn = Cast<AFTPlayerPawn>( InPawn );
	SetupHUDWidget();
}

void AFTPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
	ControlledPawn = nullptr;
}

void AFTPlayerController::OnMoveTriggered()
{
	if ( !ControlledPawn )
	{
		return;
	}

	FVector MouseWorldLocation;
	FVector MouseWorldDirection;
	if ( !DeprojectMousePositionToWorld( MouseWorldLocation, MouseWorldDirection ) )
	{
		return;
	}

	const FVector TargetPosition = FMath::LinePlaneIntersection( MouseWorldLocation,
	                                                             MouseWorldLocation + MouseWorldDirection * 10000.f,
	                                                             FVector::ZeroVector,
	                                                             FVector::UpVector );

	const FVector MovementDirection = ( TargetPosition - ControlledPawn->GetActorLocation() ).GetSafeNormal2D();
	ControlledPawn->HandleMovement( MovementDirection );
}

void AFTPlayerController::OnPause()
{
	if ( UUserWidget* PauseMenu = CreateWidget<UUserWidget>( this, GetGameInstance()->PauseMenuWidgetClass ) )
	{
		PauseMenu->AddToViewport();
		SetPause( true );
		SetInputMode( FInputModeUIOnly() );
	}
}

void AFTPlayerController::SetupHUDWidget()
{
	if ( UFTHUDWidget* HUDWidget = CreateWidget<UFTHUDWidget>( this, GetGameInstance()->HUDWidgetClass ) )
	{
		HUDWidget->BindToPlayerDelegates( ControlledPawn );
		HUDWidget->AddToViewport();
	}
	else
	{
		FT_LOG_ERROR( TEXT("Failed to create HUD Widget") )
	}
}

UFTGameInstance* AFTPlayerController::GetGameInstance()
{
	if ( !GameInstance )
	{
		GameInstance = Cast<UFTGameInstance>( GetWorld()->GetGameInstance() );
		if ( !GameInstance )
		{
			FT_LOG_ERROR( TEXT("Game Instance is invalid!") );
		}
	}
	return GameInstance;
}
