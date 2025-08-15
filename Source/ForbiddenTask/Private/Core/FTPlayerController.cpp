// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/FTPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ForbiddenTask/FTLogChannels.h"
#include "Pawns/FTPlayerPawn.h"

void AFTPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if ( UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()) )
	{
		InputSubsystem->AddMappingContext( DefaultInputMappingContext, 0 );
	}
	bShowMouseCursor = true;
}

void AFTPlayerController::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );
	
	if ( !bIsButtonDown )
	{
		return;
	}

	AFTPlayerPawn* PlayerPawn = Cast<AFTPlayerPawn>( GetPawn() );
	if ( !PlayerPawn )
	{
		return;
	}

	FVector MouseWorldLocation;
	FVector MouseWorldDirection;
	if ( !DeprojectMousePositionToWorld( MouseWorldLocation, MouseWorldDirection ) )
	{
		return;
	}

	const FVector PlaneOrigin = FVector::ZeroVector;
	const FVector PlaneNormal = FVector::UpVector;
	const FVector TargetDirection = FMath::LinePlaneIntersection( MouseWorldLocation,
	                                                        MouseWorldLocation + MouseWorldDirection * 10000.f,
	                                                        PlaneOrigin,
	                                                        PlaneNormal );

	PlayerPawn->SetTargetLocation( TargetDirection );
}

void AFTPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if ( UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>( InputComponent ) )
	{
		EnhancedInput->BindAction( MoveAction, ETriggerEvent::Triggered, this, &AFTPlayerController::OnMoveTriggered );
		EnhancedInput->BindAction( MoveAction, ETriggerEvent::Completed, this, &AFTPlayerController::OnMoveCompleted );
	}
}

void AFTPlayerController::OnMoveTriggered()
{
	FT_LOG_INFO( TEXT("Mouse Triggered") )
	bIsButtonDown = true;
}

void AFTPlayerController::OnMoveCompleted()
{
	bIsButtonDown = false;
	if ( AFTPlayerPawn* PlayerPawn = Cast<AFTPlayerPawn>( GetPawn() ) )
	{
		PlayerPawn->StopMovement();
	}
}
