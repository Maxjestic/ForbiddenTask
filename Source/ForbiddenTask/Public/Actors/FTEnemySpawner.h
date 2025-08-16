// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/FTSpawnConfigDataAsset.h"
#include "GameFramework/Actor.h"
#include "FTEnemySpawner.generated.h"

class AFTGameMode;
class UFTSpawnConfigDataAsset;

UENUM( BlueprintType )
enum class EFTSpawnerType : uint8
{
	/** Uses Actor properties to spawn enemies in a radius with curve-based Stat scaling. */
	Normal,
	/** Uses a Data Asset to define rings for spawning. */
	DataAsset,
};

/**
 * Spawns a wave of enemies at the start of the game, centered on the player location.
 * Can operate in two modes: a simple Normal mode and a more complex DataAsset mode.
 */
UCLASS()
class FORBIDDENTASK_API AFTEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	/** Sets default values. */
	AFTEnemySpawner();

protected:
	//~ Begin AActor Interface
	virtual void BeginPlay() override;
	//~ Begin AActor Interface

	/** Determines the spawning method to use. */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Spawning" )
	EFTSpawnerType SpawnerType = EFTSpawnerType::Normal;

	/** The minimum distance from the spawn center where enemies can be spawned. */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (ClampMin = "0.0") )
	float InnerRadiusThreshold = 100.f;

	// --- Normal Mode Properties ---

	/** The total number of enemies to spawn. */
	UPROPERTY( EditAnywhere,
		BlueprintReadOnly,
		Category = "Spawning|Normal Mode",
		meta = (ClampMin = "0", EditCondition = "SpawnerType == EFTSpawnerType::Normal") )
	int32 TotalEnemiesToSpawn = 1;

	/** The maximum distance from the spawn center where enemies can be spawned. */
	UPROPERTY( EditAnywhere,
		BlueprintReadOnly,
		Category = "Spawning|Normal Mode",
		meta = (ClampMin = "0.0", EditCondition = "SpawnerType == EFTSpawnerType::Normal") )
	float OuterSpawnRadius = 3000.0f;

	/** The list of possible enemy types to spawn with weights. */
	UPROPERTY( EditAnywhere,
		BlueprintReadOnly,
		Category = "Spawning|Normal Mode",
		meta = ( EditCondition = "SpawnerType == EFTSpawnerType::Normal") )
	TArray<FFTEnemySpawnInfo> EnemySpawnInfos;

	/** A curve that maps the distance from the player to the enemy Strength. */
	UPROPERTY( EditAnywhere,
		BlueprintReadOnly,
		Category = "Spawning|Normal Mode",
		meta = ( EditCondition = "SpawnerType == EFTSpawnerType::Normal") )
	TObjectPtr<UCurveFloat> StrengthOverDistanceCurve;

	/** A curve that maps the distance from the player to the enemy Speed. */
	UPROPERTY( EditAnywhere,
		BlueprintReadOnly,
		Category = "Spawning|Normal Mode",
		meta = ( EditCondition = "SpawnerType == EFTSpawnerType::Normal") )
	TObjectPtr<UCurveFloat> SpeedOverDistanceCurve;

	// --- DataAsset Mode Properties ---

	/** The configuration asset that defines the spawning zones and rules. */
	UPROPERTY( EditAnywhere,
		BlueprintReadOnly,
		Category = "Spawning|DataAsset Mode",
		meta = ( EditCondition = "SpawnerType == EFTSpawnerType::DataAsset") )
	TObjectPtr<UFTSpawnConfigDataAsset> SpawnConfig;

private:
	/** Finds the player and sets the initial PlayerPosition. Returns false if the player could not be found. */
	bool TryInitializePlayerPosition();

	/** Spawns enemies using data from the 'Normal Mode' category. */
	void SpawningNormalMode() const;

	/** Spawns enemies using data from the 'DataAsset Mode' category. */
	void SpawningDataAssetMode() const;

	/**
	 * Selects an enemy class from a weighted list.
	 * @param InEnemySpawnInfos The list of enemy types and their weights.
	 * @return The chosen enemy class to spawn.
	 */
	static TSubclassOf<AFTEnemyPawn> PickRandomEnemyType( const TArray<FFTEnemySpawnInfo>& InEnemySpawnInfos );

	/**
	 * Calculates a random spawn location
	 * @param RandomDistance Random distance from the spawn center
	 * @return Random Vector in the given distance
	 */
	FVector PickRandomSpawnLocation( const float RandomDistance ) const;

	/**
	 * Spawns a single enemy and configures it.
	 * @param EnemyClass The class of enemy to spawn.
	 * @param SpawnLocation The world location for the spawn.
	 * @param Strength The strength value for the new enemy.
	 * @param Speed The speed value for the new enemy.
	 * @param GameMode A reference to the current Game Mode to register the enemy with.
	 */
	bool TrySpawnEnemy( const TSubclassOf<AFTEnemyPawn>& EnemyClass, const FVector& SpawnLocation,
	                    const float Strength,
	                    const float Speed, AFTGameMode* GameMode ) const;

	/** The cached world position of the player at the moment spawning begins. */
	FVector PlayerPosition = FVector::ZeroVector;

#if WITH_EDITOR

public:
	/** Keeps Max <= Min in StatRanges */
	virtual void PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent ) override;
#endif
};
