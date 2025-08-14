// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SpawnConfigDataAsset.generated.h"

class AFTEnemyPawn;

/** Simple Min Max struct for stats */
USTRUCT( BlueprintType )
struct FStatRange
{
	GENERATED_BODY()

	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0") )
	float Min = 0.f;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0") )
	float Max = 0.f;
};

/** Struct connecting Enemy Class with Spawn Weight */
USTRUCT( BlueprintType )
struct FEnemySpawnInfo
{
	GENERATED_BODY()

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TSubclassOf<AFTEnemyPawn> EnemyClass;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0") )
	float SpawnWeight = 1.f;
};

/** Struct with all data needed for one zone of spawning */
USTRUCT( BlueprintType )
struct FSpawnZoneInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0"))
	float ZoneRadius = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0"))
	int32 AmountToSpawn = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FEnemySpawnInfo> EnemyTypes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FStatRange StrengthRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FStatRange SpeedRange;
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
UCLASS()
class FORBIDDENTASK_API USpawnConfigDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TArray<FSpawnZoneInfo> SpawnZones;

#if WITH_EDITOR
	/**
	 * Keeps Max <= Min for StatRanges
	 */
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
