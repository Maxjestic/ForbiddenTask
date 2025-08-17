// Copyright Maxjestic


#include "Cheats/FTCheatManager.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "ForbiddenTask/FTLogChannels.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/FTEnemyPawn.h"
#include "Pawns/FTPlayerPawn.h"

void UFTCheatManager::God()
{
	if ( AFTPlayerPawn* PlayerPawn = GetCachedPlayerPawn() )
	{
		FT_LOG_WARNING( TEXT("God Mode Toggled %s!"), PlayerPawn->ToggleGodMode() ? TEXT("ON") : TEXT("OFF") );
	}
}

void UFTCheatManager::KillPlayer()
{
	if ( AFTPlayerPawn* PlayerPawn = GetCachedPlayerPawn() )
	{
		FT_LOG_WARNING( TEXT("--CHEAT-- Player Killed.") );
		PlayerPawn->KillPlayer();
	}
}

void UFTCheatManager::KillAllEnemies() const
{
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass( GetOuterAPlayerController(), AFTEnemyPawn::StaticClass(), Enemies );

	for ( AActor* Enemy : Enemies )
	{
		Enemy->Destroy();
	}
	FT_LOG_WARNING( TEXT("--CHEAT-- All enemies Killed.") );
}

void UFTCheatManager::ToggleFreezeEnemies()
{
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass( GetOuterAPlayerController(), AFTEnemyPawn::StaticClass(), Enemies );

	for ( AActor* Enemy : Enemies )
	{
		const APawn* EnemyPawn = Cast<APawn>( Enemy );
		if ( !EnemyPawn )
		{
			continue;
		}

		const AAIController* AIController = Cast<AAIController>( EnemyPawn->GetController() );
		if ( !AIController )
		{
			continue;
		}

		UBrainComponent* Brain = AIController->GetBrainComponent();
		if ( !Brain )
		{
			continue;
		}

		if ( bAreEnemiesFrozen )
		{
			Brain->RestartLogic();
			//Enemy->CustomTimeDilation = 1.f;
		}
		else
		{
			Brain->StopLogic( TEXT( "Frozen by cheat." ) );
			//Enemy->CustomTimeDilation = 0.f;
		}
	}
	bAreEnemiesFrozen = !bAreEnemiesFrozen;
	FT_LOG_WARNING( TEXT("--CHEAT-- All enemies %s."), bAreEnemiesFrozen ? TEXT("frozen") : TEXT("unfrozen") );
}

void UFTCheatManager::SetPlayerStats( const float NewStrength, const float NewSpeed )
{
	if ( AFTPlayerPawn* PlayerPawn = GetCachedPlayerPawn() )
	{
		PlayerPawn->SetStats( NewStrength, NewSpeed );
		FT_LOG_WARNING( TEXT("--CHEAT-- Player stats set.") );
	}
}

void UFTCheatManager::AlterPlayerStats( const float StrengthDelta, const float SpeedDelta )
{
	if ( AFTPlayerPawn* PlayerPawn = GetCachedPlayerPawn() )
	{
		PlayerPawn->AlterStats( StrengthDelta, SpeedDelta );
		FT_LOG_WARNING( TEXT("--CHEAT-- Player stats altered.") );
	}
}

AFTPlayerPawn* UFTCheatManager::GetCachedPlayerPawn()
{
	if ( !CachedPlayerPawn )
	{
		CachedPlayerPawn = Cast<AFTPlayerPawn>( GetPlayerController()->GetPawn() );
	}
	return CachedPlayerPawn;
}
