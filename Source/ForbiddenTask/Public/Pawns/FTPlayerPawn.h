// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/FTBasePawn.h"
#include "FTPlayerPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;

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
	/**
	 * Default Constructor
	 * Binds function to SphereMesh overlap delegate
	 * Creates and sets default values for SpringArm and Camera
	 */
	AFTPlayerPawn();

	UFUNCTION( BlueprintCallable, Category = "Stats" )
	void AddSpeed( const float Value );

	UFUNCTION( BlueprintCallable, Category = "Stats" )
	void AddStrength( const float Value );

	UFUNCTION( BlueprintCallable, Category = "Stats" )
	void SubtractSpeed( const float Value );

	UFUNCTION( BlueprintCallable, Category = "Stats" )
	void SubtractStrength( const float Value );

protected:
	/** Callback for SphereCollider OnComponentBeginOverlap delegate */
	UFUNCTION()
	void OnBeginOverlap( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                     int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Components" )
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Components" )
	TObjectPtr<UCameraComponent> Camera;

};
