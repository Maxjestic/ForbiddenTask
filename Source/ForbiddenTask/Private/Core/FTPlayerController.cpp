// Copyright Maxjestic

#include "Core/FTPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Cheats/FTCheatManager.h"
#include "Core/FTGameInstance.h"
#include "ForbiddenTask/FTLogChannels.h"
#include "Pawns/FTPlayerPawn.h"
#include "UI/FTEndGameWidget.h"
#include "UI/FTHUDWidget.h"

AFTPlayerController::AFTPlayerController()
{
#if !UE_BUILD_SHIPPING
	CheatClass = UFTCheatManager::StaticClass();
#endif // !UE_BUILD_SHIPPING
}

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
		//bShowMouseCursor = true;
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
		if ( ensureMsgf( MoveAction, TEXT("Move Action is invalid!") ) )
		{
			EnhancedInput->BindAction( MoveAction, ETriggerEvent::Triggered,this, &AFTPlayerController::OnMoveTriggered );
		}
		
		if ( ensureMsgf( PauseAction, TEXT("Pause Action is invalid!") ) )
		{
			EnhancedInput->BindAction( PauseAction, ETriggerEvent::Triggered, this, &AFTPlayerController::TogglePause );
		}

#if !UE_BUILD_SHIPPING
		if ( ensureMsgf( CheatMenuAction, TEXT("Cheat Menu Action is invalid!") ) )
		{
			EnhancedInput->BindAction( CheatMenuAction, ETriggerEvent::Triggered,this, &AFTPlayerController::ToggleCheatMenu );			
		}
#endif // !UE_BUILD_SHIPPING
	}
}

void AFTPlayerController::OnPossess( APawn* InPawn )
{
	Super::OnPossess( InPawn );
	ControlledPawn = Cast<AFTPlayerPawn>( InPawn );
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

void AFTPlayerController::TogglePause()
{
	if ( PauseMenu && PauseMenu->IsInViewport() )
	{
		HandleUnpause();
	}
	else
	{
		HandlePause();
	}
}

void AFTPlayerController::HandlePause()
{
	if ( !GetGameInstance()->PauseMenuWidgetClass )
	{
		FT_LOG_ERROR( TEXT("Pause Menu Widget Class is invalid!") );
		return;
	}

	PauseMenu = CreateWidget<UUserWidget>( this, GetGameInstance()->PauseMenuWidgetClass );
	if ( !PauseMenu )
	{
		FT_LOG_ERROR( TEXT("Failed to create Pause Menu Widget") );
		return;
	}
	PauseMenu->AddToViewport();

	SetPause( true );

	FInputModeGameAndUI InputModeData;
	InputModeData.SetWidgetToFocus( PauseMenu->TakeWidget() );
	InputModeData.SetLockMouseToViewportBehavior( EMouseLockMode::DoNotLock );
	InputModeData.SetHideCursorDuringCapture( false );

	SetInputMode( InputModeData );
}

void AFTPlayerController::HandleUnpause()
{
	PauseMenu->RemoveFromParent();
	PauseMenu = nullptr;

	SetPause( false );
	SetInputMode( FInputModeGameAndUI() );
	bShowMouseCursor = true;
}

void AFTPlayerController::ToggleCheatMenu()
{
	if ( CheatMenu && CheatMenu->IsInViewport() )
	{
		CheatMenu->RemoveFromParent();
		bShowMouseCursor = true;
		return;
	}
	if ( !CheatMenu && !CreateCheatMenu() )
	{		
		return;
	}

	CheatMenu->AddToViewport();

	FInputModeGameAndUI InputModeData;
	InputModeData.SetWidgetToFocus( CheatMenu->TakeWidget() );
	InputModeData.SetLockMouseToViewportBehavior( EMouseLockMode::DoNotLock );
	InputModeData.SetHideCursorDuringCapture( false );
	SetInputMode( InputModeData );

	bShowMouseCursor = true;
}

bool AFTPlayerController::CreateCheatMenu()
{
	if ( const UFTGameInstance* GameInstance = GetGameInstance() )
	{
		CheatMenu = CreateWidget<UUserWidget>( this, GameInstance->CheatMenuWidgetClass );
		if ( !CheatMenu )
		{
			FT_LOG_ERROR( TEXT("Failed to create Cheat Menu Widget") );
			return false;
		}
	}
	return true;
}

UFTGameInstance* AFTPlayerController::GetGameInstance()
{
	if ( !CachedGameInstance )
	{
		CachedGameInstance = Cast<UFTGameInstance>( GetWorld()->GetGameInstance() );
		if ( !CachedGameInstance )
		{
			FT_LOG_ERROR( TEXT("Game Instance is invalid!") );
		}
	}
	return CachedGameInstance;
}
