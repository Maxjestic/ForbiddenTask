// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/FTPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
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
	ControlledPawn = Cast<AFTBasePawn>( InPawn );
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
	
	const FVector MovementDirection = (TargetPosition - ControlledPawn->GetActorLocation() ).GetSafeNormal2D();
	ControlledPawn->HandleMovement( MovementDirection );
}
