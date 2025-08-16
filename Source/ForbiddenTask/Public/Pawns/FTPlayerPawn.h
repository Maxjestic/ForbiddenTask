// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "Pawns/FTBasePawn.h"
#include "FTPlayerPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnPlayerStatChanged, float, NewValue );

/**
 * Represents the player-controlled pawn in the game, inheriting from AFTBasePawn.
 * Provides functionality for player movement, collision and altering stats.
 * And Lose condition
 */
UCLASS( Blueprintable )
class FORBIDDENTASK_API AFTPlayerPawn : public AFTBasePawn
{
	GENERATED_BODY()

public:
	/** Sets up player-specific components and default values. */
	AFTPlayerPawn();

	UFUNCTION( BlueprintCallable, Category = "Stats" )
	void AddSpeed( const float Value );

	UFUNCTION( BlueprintCallable, Category = "Stats" )
	void AddStrength( const float Value );

	UFUNCTION( BlueprintCallable, Category = "Stats" )
	void SubtractSpeed( const float Value );

	UFUNCTION( BlueprintCallable, Category = "Stats" )
	void SubtractStrength( const float Value );

	UFUNCTION( BLueprintPure, Category = "Stats" )
	FORCEINLINE float GetMaxStrength() const { return MaxStrength; };

	UFUNCTION( BlueprintPure, Category = "Stats" )
	FORCEINLINE float GetMaxSpeed() const { return MaxSpeed; };

	/** Delegate broadcast when Strength changes. Passes the new current strength. */
	UPROPERTY( BlueprintAssignable, Category = "Events" )
	FOnPlayerStatChanged OnStrengthChanged;

	/** Delegate broadcast when Speed changes. Passes the new current speed. */
	UPROPERTY( BlueprintAssignable, Category = "Events" )
	FOnPlayerStatChanged OnSpeedChanged;

protected:
	/** Callback for SphereCollider OnComponentBeginOverlap delegate */
	UFUNCTION()
	void OnBeginOverlap( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                     int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Components" )
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Components" )
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Stats" )
	float MaxStrength = 100.f;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Stats" )
	float MaxSpeed = 100.f;

private:
	/** Check Strength after change and performs necessary actions */
	void StrengthCheck();

	/** Check Strength after change and performs necessary actions */
	void SpeedCheck();

	/** To ensure death broadcast only happens once. */
	bool bIsAlive = true;
};
