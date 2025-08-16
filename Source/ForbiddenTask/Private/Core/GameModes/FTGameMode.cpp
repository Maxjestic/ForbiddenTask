// Copyright Maxjestic

#include "Core/GameModes/FTGameMode.h"

#include "Core/FTPlayerController.h"
#include "ForbiddenTask/FTLogChannels.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/FTBasePawn.h"

void AFTGameMode::RegisterEnemy( AFTBasePawn* NewEnemy )
{
	if ( !NewEnemy )
	{
		return;
	}

	AliveEnemies++;
	FT_LOG_INFO( TEXT("Enemy %d registered"), AliveEnemies )
	NewEnemy->OnPawnDied.AddDynamic( this, &AFTGameMode::AFTGameMode::HandleEnemyDied );
}

void AFTGameMode::HandleStartingNewPlayer_Implementation( APlayerController* NewPlayer )
{
	Super::HandleStartingNewPlayer_Implementation( NewPlayer );

	FT_LOG_INFO( TEXT("OnPostLogin"), AliveEnemies )

	if ( AFTBasePawn* PlayerPawn = Cast<AFTBasePawn>( NewPlayer->GetPawn() ) )
	{
		FT_LOG_INFO( TEXT("Player registered"), AliveEnemies )
		PlayerPawn->OnPawnDied.AddDynamic( this, &AFTGameMode::HandlePlayerDeath );
	}
}

void AFTGameMode::HandleEnemyDied( AFTBasePawn* DeadEnemy )
{
	if ( !DeadEnemy )
	{
		return;
	}

	DeadEnemy->OnPawnDied.RemoveDynamic( this, &AFTGameMode::AFTGameMode::HandleEnemyDied );

	--AliveEnemies;
	FT_LOG_INFO( TEXT("Enemy died. Enemies left: %d"), AliveEnemies )
	if ( AliveEnemies <= 0 )
	{
		EndGame( true );
	}
}

void AFTGameMode::HandlePlayerDeath( AFTBasePawn* DeadPlayer )
{
	if ( !DeadPlayer )
	{
		return;
	}
	DeadPlayer->OnPawnDied.RemoveDynamic( this, &AFTGameMode::HandlePlayerDeath );

	EndGame( false );
}

void AFTGameMode::EndGame( const bool bPlayerWon )
{
	if ( bIsGameOver )
	{
		return;
	}
	bIsGameOver = true;

	if (AFTPlayerController* PlayerController = Cast<AFTPlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
	{
		// Tell the controller to handle the UI.
		PlayerController->ShowEndScreen(bPlayerWon);
	}
}
