// Copyright Maxjestic

#include "Core/GameModes/FTGameMode.h"

#include "Core/FTPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/FTBasePawn.h"

void AFTGameMode::RegisterEnemy( AFTBasePawn* NewEnemy )
{
	if ( !NewEnemy )
	{
		return;
	}

	AliveEnemies++;
	NewEnemy->OnPawnDied.AddDynamic( this, &AFTGameMode::HandleEnemyDied );
}

void AFTGameMode::HandleStartingNewPlayer_Implementation( APlayerController* NewPlayer )
{
	Super::HandleStartingNewPlayer_Implementation( NewPlayer );

	if ( AFTBasePawn* PlayerPawn = Cast<AFTBasePawn>( NewPlayer->GetPawn() ) )
	{
		PlayerPawn->OnPawnDied.AddDynamic( this, &AFTGameMode::HandlePlayerDeath );
	}
}

void AFTGameMode::HandleEnemyDied( AFTBasePawn* DeadEnemy )
{
	if ( !DeadEnemy )
	{
		return;
	}

	DeadEnemy->OnPawnDied.RemoveDynamic( this, &AFTGameMode::HandleEnemyDied );

	AliveEnemies--;
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
		PlayerController->ShowEndScreen(bPlayerWon);
	}
}
