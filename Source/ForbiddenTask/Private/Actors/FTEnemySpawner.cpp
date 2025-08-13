// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FTEnemySpawner.h"

#include "DataAssets/SpawnConfigDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/FTEnemyPawn.h"

AFTEnemySpawner::AFTEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AFTEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	const APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn( GetWorld(), 0 );
	if ( !IsValid( PlayerPawn ) )
	{
		UE_LOG( LogTemp, Error, TEXT( "PlayerPawn is invalid - In EnemySpawner!" ) );
		return;
	}
	PlayerPosition = PlayerPawn->GetActorLocation();

	switch ( SpawnerType )
	{
	case ESpawnerType::Normal:
		SpawnNormal();
		break;
	case ESpawnerType::DataAsset:
		SpawnDataAsset();
		break;
	}
}

void AFTEnemySpawner::SpawnNormal() const
{
	if ( EnemySpawnInfos.IsEmpty() || !StrengthOverDistanceCurve || !SpeedOverDistanceCurve )
	{
		UE_LOG( LogTemp, Error, TEXT( "Necessary data for Normal Spawn Mode missing!" ) );
		return;
	}

	for ( int32 i = 0; i < TotalEnemiesToSpawn; i++ )
	{
		const float RandomDistance = FMath::FRandRange( RadiusThreshold, SpawnRadius );
		const FVector SpawnLocation = GetRandomSpawnLocation( RandomDistance );

		TSubclassOf<AFTEnemyPawn> SelectedEnemyClass = GetRandomEnemyType( EnemySpawnInfos );
		if ( !SelectedEnemyClass ) continue;

		const float Strength = StrengthOverDistanceCurve->GetFloatValue( RandomDistance / SpawnRadius );
		const float Speed = SpeedOverDistanceCurve->GetFloatValue( RandomDistance / SpawnRadius );
		
		SpawnEnemy( SelectedEnemyClass, SpawnLocation, Strength, Speed );
	}
}

void AFTEnemySpawner::SpawnDataAsset() const
{
	if ( !SpawnConfig )
	{
		UE_LOG( LogTemp, Error, TEXT("Necessary data for Data Asset Spawn Mode missing!") );
		return;
	}

	float MinDistance = RadiusThreshold;

	for ( const FSpawnZoneInfo& ZoneInfo : SpawnConfig->SpawnZones )
	{
		for ( int32 i = 0; i < ZoneInfo.AmountToSpawn; i++ )
		{
			const float RandomDistance = FMath::FRandRange( MinDistance, MinDistance + ZoneInfo.ZoneRadius );
			const FVector SpawnLocation = GetRandomSpawnLocation( RandomDistance );

			const TSubclassOf<AFTEnemyPawn> SelectedEnemyClass = GetRandomEnemyType( ZoneInfo.EnemyTypes );
			if ( !SelectedEnemyClass ) continue;

			const float Strength = FMath::FRandRange( ZoneInfo.StrengthRange.Min, ZoneInfo.StrengthRange.Max );
			const float Speed = FMath::FRandRange( ZoneInfo.SpeedRange.Min, ZoneInfo.SpeedRange.Max );
			SpawnEnemy( SelectedEnemyClass, SpawnLocation, Strength, Speed );
		}
		MinDistance += ZoneInfo.ZoneRadius;
	}
}

TSubclassOf<AFTEnemyPawn> AFTEnemySpawner::GetRandomEnemyType( const TArray<FEnemySpawnInfo>& InEnemySpawnInfos )
{
	float TotalWeight = 0.f;
	for ( const FEnemySpawnInfo& Info : InEnemySpawnInfos )
	{
		TotalWeight += Info.SpawnWeight;
	}

	float RandomSelection = FMath::FRandRange( 0.f, TotalWeight );
	for ( const FEnemySpawnInfo& Info : InEnemySpawnInfos )
	{
		RandomSelection -= Info.SpawnWeight;
		if ( RandomSelection <= 0.f )
		{
			return Info.EnemyClass;
		}
	}

	return nullptr;
}

FVector AFTEnemySpawner::GetRandomSpawnLocation( const float& RandomDistance ) const
{
	const float RandomAngle = FMath::FRandRange( 0.f, 360.f );
	const float Radians = FMath::DegreesToRadians( RandomAngle );
	FVector SpawnLocation = PlayerPosition;
	SpawnLocation.X += RandomDistance * FMath::Cos( Radians );
	SpawnLocation.Y += RandomDistance * FMath::Sin( Radians );
	return SpawnLocation;
}

void AFTEnemySpawner::SpawnEnemy( const TSubclassOf<AFTEnemyPawn>& EnemyClass, const FVector& SpawnLocation,
	const float& Strength, const float& Speed ) const
{
	AFTEnemyPawn* SpawnedEnemy = GetWorld()->SpawnActor<AFTEnemyPawn>(
			EnemyClass,
			SpawnLocation,
			FRotator::ZeroRotator );
	if ( SpawnedEnemy )
	{		
		SpawnedEnemy->SetStats( Strength, Speed );
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
