// Copyright Maxjestic

#include "Actors/FTEnemySpawner.h"

#include "DataAssets/FTSpawnConfigDataAsset.h"
#include "ForbiddenTask/FTLogChannels.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/FTEnemyPawn.h"

AFTEnemySpawner::AFTEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AFTEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	if ( !TryInitializePlayerPosition() )
	{
		return;
	}

	switch ( SpawnerType )
	{
	case EFTSpawnerType::Normal:
		SpawningNormalMode();
		break;
	case EFTSpawnerType::DataAsset:
		SpawningDataAssetMode();
		break;
	}
}

bool AFTEnemySpawner::TryInitializePlayerPosition()
{
	const APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn( GetWorld(), 0 );
	if ( !IsValid( PlayerPawn ) )
	{
		FT_LOG_ERROR( TEXT( "PlayerPawn is invalid!" ) );
		return false;
	}
	PlayerPosition = PlayerPawn->GetActorLocation();
	return true;
}

void AFTEnemySpawner::SpawningNormalMode() const
{
	if ( EnemySpawnInfos.IsEmpty() || !StrengthOverDistanceCurve || !SpeedOverDistanceCurve )
	{
		FT_LOG_ERROR( TEXT("Necessary data for Normal Spawn Mode missing!") );
		return;
	}

	for ( int32 i = 0; i < TotalEnemiesToSpawn; i++ )
	{
		const float RandomDistance = FMath::FRandRange( RadiusThreshold, SpawnRadius );
		const FVector SpawnLocation = PickRandomSpawnLocation( RandomDistance );

		TSubclassOf<AFTEnemyPawn> SelectedEnemyClass = PickRandomEnemyType( EnemySpawnInfos );
		if ( !SelectedEnemyClass ) continue;

		const float Strength = StrengthOverDistanceCurve->GetFloatValue( RandomDistance / SpawnRadius );
		const float Speed = SpeedOverDistanceCurve->GetFloatValue( RandomDistance / SpawnRadius );

		SpawnEnemy( SelectedEnemyClass, SpawnLocation, Strength, Speed );
	}
}

void AFTEnemySpawner::SpawningDataAssetMode() const
{
	if ( !SpawnConfig )
	{
		FT_LOG_ERROR( TEXT("Necessary data for Data Asset Spawn Mode missing!") );
		return;
	}

	float MinDistance = RadiusThreshold;

	for ( const FFTSpawnZoneInfo& ZoneInfo : SpawnConfig->SpawnZones )
	{
		for ( int32 i = 0; i < ZoneInfo.AmountToSpawn; i++ )
		{
			const float RandomDistance = FMath::FRandRange( MinDistance, MinDistance + ZoneInfo.ZoneRadius );
			const FVector SpawnLocation = PickRandomSpawnLocation( RandomDistance );

			const TSubclassOf<AFTEnemyPawn> SelectedEnemyClass = PickRandomEnemyType( ZoneInfo.EnemyTypes );
			if ( !SelectedEnemyClass ) continue;

			const float Strength = FMath::FRandRange( ZoneInfo.StrengthRange.Min, ZoneInfo.StrengthRange.Max );
			const float Speed = FMath::FRandRange( ZoneInfo.SpeedRange.Min, ZoneInfo.SpeedRange.Max );
			SpawnEnemy( SelectedEnemyClass, SpawnLocation, Strength, Speed );
		}
		MinDistance += ZoneInfo.ZoneRadius;
	}
}

TSubclassOf<AFTEnemyPawn> AFTEnemySpawner::PickRandomEnemyType( const TArray<FFTEnemySpawnInfo>& InEnemySpawnInfos )
{
	float TotalWeight = 0.f;
	for ( const FFTEnemySpawnInfo& Info : InEnemySpawnInfos )
	{
		TotalWeight += Info.SpawnWeight;
	}

	float RandomSelection = FMath::FRandRange( 0.f, TotalWeight );
	for ( const FFTEnemySpawnInfo& Info : InEnemySpawnInfos )
	{
		RandomSelection -= Info.SpawnWeight;
		if ( RandomSelection <= 0.f )
		{
			return Info.EnemyClass;
		}
	}

	return nullptr;
}

FVector AFTEnemySpawner::PickRandomSpawnLocation( const float RandomDistance ) const
{
	const float RandomAngle = FMath::FRandRange( 0.f, 360.f );
	const float Radians = FMath::DegreesToRadians( RandomAngle );
	FVector SpawnLocation = PlayerPosition;
	SpawnLocation.X += RandomDistance * FMath::Cos( Radians );
	SpawnLocation.Y += RandomDistance * FMath::Sin( Radians );
	return SpawnLocation;
}

void AFTEnemySpawner::SpawnEnemy( const TSubclassOf<AFTEnemyPawn>& EnemyClass, const FVector& SpawnLocation,
                                  const float Strength, const float Speed ) const
{
	AFTEnemyPawn* SpawnedEnemy = GetWorld()->SpawnActor<AFTEnemyPawn>(
		EnemyClass,
		SpawnLocation,
		FRotator::ZeroRotator );
	if ( SpawnedEnemy )
	{
		SpawnedEnemy->SetStats( Strength, Speed );
		// TODO: Connect with GameMode for win condition
		// TODO: Enemies can spawn on each other, return true and add while 
	}
}

#if WITH_EDITOR
void AFTEnemySpawner::PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent )
{
	Super::PostEditChangeProperty( PropertyChangedEvent );

	if ( SpawnRadius < RadiusThreshold )
	{
		SpawnRadius = RadiusThreshold;
	}
}
#endif // WITH_EDITOR
