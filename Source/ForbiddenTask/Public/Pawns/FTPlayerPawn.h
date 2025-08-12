// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/FTBasePawn.h"
#include "FTPlayerPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;

/**
 * Player Class
 * Handles movement
 */
UCLASS()
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

	//~ Begin AActor Interface
	virtual void Tick( float DeltaSeconds ) override;
	//~ End AActor Interface

	/**
	 * Called by PlayerController every Tick when the mouse button is pressed.
	 * Sets the target-related properties
	 * @param NewTargetLocation Position of the cursor in world space
	 */
	void SetTargetLocation( const FVector& NewTargetLocation );

	/**
	 * Called by PlayerController when the mouse button is released.
	 * Sets the mouse location properties
	 */
	void StopMovement();

	/**
	 * Alters stats by passed values.
	 * @param SpeedChange Value will be added to the Speed value. Can be negative.
	 * @param StrengthChange Value will be added to the Strength value. Can be negative.
	 */
	void ChangeStats( const float& SpeedChange, const float& StrengthChange );

protected:
	UFUNCTION()
	void OnOverlapBegin( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                     int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Components" )
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Components" )
	TObjectPtr<UCameraComponent> Camera;

private:
	
	FVector MouseLocation;
	bool bHasMouseLocation = false;
};
