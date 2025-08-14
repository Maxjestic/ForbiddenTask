// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/SpawnConfigDataAsset.h"
#include "GameFramework/Actor.h"
#include "FTEnemySpawner.generated.h"

class USpawnConfigDataAsset;

UENUM( BlueprintType )
enum class ESpawnerType : uint8
{
	// TODO: add comment
	Normal,
	DataAsset,
};

/**
 * Class for EnemySpawner
 * Spawns enemies using SpawnConfigDataAsset
 */
UCLASS()
class FORBIDDENTASK_API AFTEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	/**
	 * Default Constructor
	 * Sets tick
	 */
	AFTEnemySpawner();

protected:
	//~ Begin AActor Interface
	virtual void BeginPlay() override;
	//~ Begin AActor Interface

	/**
	 * Type of spawner
	 * Normal - Uses radius and common data for the whole area
	 * DataAsset - Uses data specified in DataAsset
	 */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Spawning" )
	ESpawnerType SpawnerType = ESpawnerType::Normal;

	/**
	 * Used to prevent enemies spawning on the Player
	 */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (ClampMin = "0.0") )
	float RadiusThreshold = 100.f;

	/**
	 * The total number of enemies to spawn, used only for Non-DataAsset Mode
	 */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Spawning|Normal Mode", meta = (ClampMin = "0") )
	int32 TotalEnemiesToSpawn = 1;

	/**
	 * Max spawn distance from the player
	 */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Spawning|Normal Mode", meta = (ClampMin = "0.0") )
	float SpawnRadius = 3000.0f;

	/**
	 * The list of possible enemy types to spawn with weight
	 */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Spawning|Normal Mode" )
	TArray<FEnemySpawnInfo> EnemySpawnInfos;

	// --- Curve assets for stat scaling --- //
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Spawning|Normal Mode" )
	TObjectPtr<UCurveFloat> StrengthOverDistanceCurve;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Spawning|Normal Mode" )
	TObjectPtr<UCurveFloat> SpeedOverDistanceCurve;

	/**
	 * Used for DataAsset Mode
	 */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Spawning|DataAsset Mode" )
	TObjectPtr<USpawnConfigDataAsset> SpawnConfig;

private:
	/**
	 * Called if Spawner Mode is set to Normal
	 * Uses random position in a given radius and Curves for Stats
	 */
	void SpawnNormal() const;

	/**
	 * Called if Spawner Mode is set to DataAsset
	 * Uses DataAsset with values for each ring in a spawning zone
	 */
	void SpawnDataAsset() const;

	/**
	 * Picks random Enemy Class based on set Weights
	 * @param InEnemySpawnInfos Array of all EnemySpawnInfo considered
	 * @return Random Class of picked enemy type
	 */
	static TSubclassOf<AFTEnemyPawn> PickRandomEnemyType( const TArray<FEnemySpawnInfo>& InEnemySpawnInfos );

	/**
	 * Picks random spawn location
	 * @param RandomDistance Random distance from Player position for spawn
	 * @return Random location in a given radius
	 */
	FVector PickRandomSpawnLocation( const float RandomDistance ) const;

	/**
	 * Spawns Enemy and sets its Stats
	 * @param EnemyClass Type of Enemy to spawn
	 * @param SpawnLocation Location for spawn
	 * @param Strength for the Enemy
	 * @param Speed for the Enemy
	 */
	void SpawnEnemy( const TSubclassOf<AFTEnemyPawn>& EnemyClass, const FVector& SpawnLocation,
	                 const float Strength,
	                 const float Speed ) const;

	FVector PlayerPosition = FVector::ZeroVector;

public:
#if WITH_EDITOR
	/**
	 * Keeps Max <= Min for StatRanges
	 */
	virtual void PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent ) override;
#endif
};
