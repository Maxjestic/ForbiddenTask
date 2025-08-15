// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FTSpawnConfigDataAsset.generated.h"

class AFTEnemyPawn;

/** Simple Min Max struct for stats */
USTRUCT( BlueprintType )
struct FFTStatRange
{
	GENERATED_BODY()

	/** Minimum value for the Stat */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0") )
	float Min = 0.f;

	/** Maximum value for the stat */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0") )
	float Max = 0.f;
};

/** Struct for Enemy Class with Spawn Weight */
USTRUCT( BlueprintType )
struct FFTEnemySpawnInfo
{
	GENERATED_BODY()

	/** Class of the Enemy */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TSubclassOf<AFTEnemyPawn> EnemyClass;

	/** Higher the number higher the possibility of this Enemy Type to get spawned */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0") )
	float SpawnWeight = 1.f;
};

/** Struct with all data needed for one zone of spawning */
USTRUCT( BlueprintType )
struct FFTSpawnZoneInfo
{
	GENERATED_BODY()

	/** Radius of the zone - Extent of the next zone */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0") )
	float ZoneRadius = 0.f;

	/** Number of Enemies that will be spawned in the zone */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0") )
	int32 AmountToSpawn = 0;

	/** Types of Enemies that will be spawned in the zone with weights */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TArray<FFTEnemySpawnInfo> EnemyTypes;

	/** Range for a random strength value that will be assigned to the Enemy (recalculated for each) */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FFTStatRange StrengthRange;

	/** Range for a random speed value that will be assigned to the Enemy (recalculated for each) */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FFTStatRange SpeedRange;
};

/**
 * Data Asset used to store details about spawning.
 * Each Entry in SpawnZones contains spawning settings in a given zone
 *
 * Example:
 * [0] - ZoneRadius = 200, AmountToSpawn = 10
 * [1] - ZoneRadius = 100, AmountToSpawn = 5
 * 0. Radius = 0;
 * 1. Spawner spawns 10 enemies in Radius (0) - Radius + 200; Radius = 200
 * 2. Spawner spawns 5 enemies in Radius (200) - Radius + 100; Radius = 300
 */
UCLASS( Blueprintable )
class FORBIDDENTASK_API UFTSpawnConfigDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** Info for all zones that can be used by the Spawner */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TArray<FFTSpawnZoneInfo> SpawnZones;

#if WITH_EDITOR
	/** Keeps Max <= Min for StatRanges */
	virtual void PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent ) override;
#endif
};
