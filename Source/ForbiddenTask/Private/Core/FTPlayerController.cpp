// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/FTPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Core/FTGameInstance.h"
#include "ForbiddenTask/FTLogChannels.h"
#include "Pawns/FTPlayerPawn.h"
#include "UI/FTHUDWidget.h"

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

void AFTPlayerController::SetupHUDWidget()
{
	const UFTGameInstance* GameInstance = GetGameInstance<UFTGameInstance>();
	if ( !GameInstance )
	{
		FT_LOG_ERROR( TEXT("Wrong Game Instance") )
	}

	if ( UFTHUDWidget* HUDWidget = CreateWidget<UFTHUDWidget>( this, GameInstance->HUDWidgetClass ) )
	{
		HUDWidget->BindToPlayerDelegates( ControlledPawn );
		HUDWidget->AddToViewport();
	}
	else
	{
		FT_LOG_ERROR( TEXT("Failed to create HUD Widget") )
	}
}
