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
	/**
	 * Uses radius to define area for spawning
	 * Number of Enemies and provided Enemy Types with weight to spawn Enemies
	 * Curves for distance - power relation.
	 */
	Normal,
	/**
	 * Uses DataAsset for ring-like areas around the spawn center point
	 * Data from DataAsset is used for Enemy spawning details (Power, chance of spawning, types, etc.)
	 */
	DataAsset,
};

/**
 * Class for EnemySpawner
 * Spawns enemies around Player 
 * Values in Properties (Normal Mode)
 * Values from DataAsset (DataAsset Mode)
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
	EFTSpawnerType SpawnerType = EFTSpawnerType::Normal;

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
	TArray<FFTEnemySpawnInfo> EnemySpawnInfos;

	// --- Curve assets for stat scaling --- //
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Spawning|Normal Mode" )
	TObjectPtr<UCurveFloat> StrengthOverDistanceCurve;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Spawning|Normal Mode" )
	TObjectPtr<UCurveFloat> SpeedOverDistanceCurve;

	/**
	 * Used for DataAsset Mode
	 */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Spawning|DataAsset Mode" )
	TObjectPtr<UFTSpawnConfigDataAsset> SpawnConfig;

private:
	/**
	 * Tries to find the Player and get its position in World Space
	 * @return True - Success, False - Failed
	 */
	bool TryInitializePlayerPosition();

	/**
	 * Called if Spawner Mode is set to Normal
	 * Uses random position in a given radius and Curves for Stats
	 */
	void SpawningNormalMode() const;

	/**
	 * Called if Spawner Mode is set to DataAsset
	 * Uses DataAsset with values for each ring in a spawning zone
	 */
	void SpawningDataAssetMode() const;

	/**
	 * Picks random Enemy Class based on set Weights
	 * @param InEnemySpawnInfos Array of all EnemySpawnInfo considered
	 * @return Random Class of picked enemy type
	 */
	static TSubclassOf<AFTEnemyPawn> PickRandomEnemyType( const TArray<FFTEnemySpawnInfo>& InEnemySpawnInfos );

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
	 * @param GameMode used to register Enemy
	 * @return if spawning was successful
	 */
	bool TrySpawnEnemy( const TSubclassOf<AFTEnemyPawn>& EnemyClass, const FVector& SpawnLocation,
	                 const float Strength,
	                 const float Speed, AFTGameMode* GameMode ) const;

	FVector PlayerPosition = FVector::ZeroVector;

#if WITH_EDITOR

public:
	/**
	 * Keeps Max <= Min for StatRanges
	 */
	virtual void PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent ) override;
#endif
};
