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

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Spawning" )
	ESpawnerType SpawnerType = ESpawnerType::Normal;

	/**
	 * The total number of enemies to spawn, used only for Non-DataAsset Mode
	 */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (ClampMin = "0") )
	int32 TotalEnemiesToSpawn = 1;

	/**
	 * Max spawn distance from the player
	 */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (ClampMin = "0.0") )
	float SpawnRadius = 3000.0f;

	/**
	 * Used to prevent enemies spawning on the Player
	 */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (ClampMin = "0.0") )
	float RadiusThreshold = 100.f;

	/**
	 * The list of possible enemy types to spawn with weight
	 */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Spawning" )
	TArray<FEnemySpawnInfo> EnemySpawnInfos;

	/**
	 * Curve assets for stat scaling
	 */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Spawning|Scaling" )
	TObjectPtr<UCurveFloat> StrengthOverDistanceCurve;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Spawning|Scaling" )
	TObjectPtr<UCurveFloat> SpeedOverDistanceCurve;

	/**
	 * Used for DataAsset Mode
	 */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Spawning" )
	TObjectPtr<USpawnConfigDataAsset> SpawnConfig;

private:
	void SpawnNormal() const;

	void SpawnDataAsset() const;

	static TSubclassOf<AFTEnemyPawn> GetRandomEnemyType( const TArray<FEnemySpawnInfo>& InEnemySpawnInfos );

	FVector GetRandomSpawnLocation( const float& RandomDistance ) const;

	void SpawnEnemy( const TSubclassOf<AFTEnemyPawn>& EnemyClass, const FVector& SpawnLocation,
	                 const float& Strength,
	                 const float& Speed ) const;

	FVector PlayerPosition = FVector::ZeroVector;

public:
#if WITH_EDITOR
	/**
	 * Keeps Max <= Min for StatRanges
	 */
	virtual void PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent ) override;
#endif
};
