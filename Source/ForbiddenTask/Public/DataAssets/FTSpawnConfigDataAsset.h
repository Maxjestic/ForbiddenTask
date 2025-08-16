// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FTSpawnConfigDataAsset.generated.h"

class AFTEnemyPawn;

/** Simple Min Max struct for stats. */
USTRUCT( BlueprintType )
struct FFTStatRange
{
	GENERATED_BODY()

	/** Minimum value for the Stat. */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0") )
	float Min = 0.f;

	/** Maximum value for the stat. */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0") )
	float Max = 0.f;
};

/** Struct for Enemy Class with Spawn Weight */
USTRUCT( BlueprintType )
struct FFTEnemySpawnInfo
{
	GENERATED_BODY()

	/** Class of the Enemy */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TSubclassOf<AFTEnemyPawn> EnemyClass;

	/** Higher the number higher the possibility of this Enemy Type to get spawned */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.1") )
	float SpawnWeight = 1.f;
};

/** Struct with all data needed for one zone of spawning */
USTRUCT( BlueprintType )
struct FFTSpawnZoneInfo
{
	GENERATED_BODY()

    /** The outer radius of this zone, extending from the previous zone's radius. */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0") )
	float ZoneRadius = 500.f;

	/** Number of Enemies that will be spawned in this zone */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0") )
	int32 AmountToSpawn = 5;

	/** Types of Enemies that will be spawned in the zone with weights */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TArray<FFTEnemySpawnInfo> EnemyTypes;

    /** Range for a random strength value that will be assigned to the Enemy. */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FFTStatRange StrengthRange;

    /** Range for a random speed value that will be assigned to the Enemy. */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FFTStatRange SpeedRange;
};

/**
 * Data Asset used to store details about zone-based spawning.
 * Each entry in SpawnZones defines a ring and its spawning rules.
 */
UCLASS( Blueprintable )
class FORBIDDENTASK_API UFTSpawnConfigDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
    /** The array of spawn zones, processed in order from the center outwards. */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TArray<FFTSpawnZoneInfo> SpawnZones;

#if WITH_EDITOR
	/** Keeps Max <= Min for StatRanges */
	virtual void PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent ) override;
#endif
};
