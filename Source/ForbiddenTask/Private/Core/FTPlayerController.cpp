// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/FTPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Pawns/FTPlayerPawn.h"

void AFTPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if ( UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>( InputComponent ) )
	{
		EnhancedInput->BindAction( MoveAction, ETriggerEvent::Triggered, this, &AFTPlayerController::OnMoveTriggered );
		EnhancedInput->BindAction( MoveAction, ETriggerEvent::Completed, this, &AFTPlayerController::OnMoveCompleted );
	}
}

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

	FVector WorldLocation;
	FVector WorldDirection;
	if ( !DeprojectMousePositionToWorld( WorldLocation, WorldDirection ) )
	{
		return;
	}

	const FVector PlaneOrigin = FVector::ZeroVector;
	const FVector PlaneNormal = FVector::UpVector;
	const FVector TargetDirection = FMath::LinePlaneIntersection( WorldLocation,
	                                                        WorldLocation + WorldDirection * 10000.f,
	                                                        PlaneOrigin,
	                                                        PlaneNormal );

	PlayerPawn->SetTargetLocation( TargetDirection );
}

void AFTPlayerController::OnMoveTriggered()
{
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
