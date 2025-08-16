// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FTBasePawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnPawnDiedSignature, AFTBasePawn*, DeadEnemy );

class USphereComponent;

/**
 * AFTBasePawn serves as the base class for all controllable pawns in the Forbidden Task Project.
 * It handles shared logic for physics-based movement and stats.
 */
UCLASS( Abstract, NotBlueprintable )
class FORBIDDENTASK_API AFTBasePawn : public APawn
{
	GENERATED_BODY()

public:
	/** Sets default values and creates components. */
	AFTBasePawn();

	/** Applies a continuous force based on the pawn's speed and the provided direction. */
	virtual void HandleMovement( const FVector& ForceDirection );

	/** Sets both Strength and Speed and handles any resulting state changes. */
	void SetStats( const float NewStrength, const float NewSpeed );

	UFUNCTION( BlueprintPure, Category = "Stats" )
	FORCEINLINE float GetStrength() const { return Strength; };

	UFUNCTION( BlueprintPure, Category = "Stats" )
	FORCEINLINE float GetSpeed() const { return Speed; };

	/** Delegate broadcast just before this pawn is destroyed. */
	UPROPERTY( BlueprintAssignable, Category = "Events" )
	FOnPawnDiedSignature OnPawnDied;

protected:
	//~ Begin AActor Interface
	virtual void OnConstruction( const FTransform& Transform ) override;
	//~ End AActor Interface

	/** Updates the visual scale of the pawn based on its current Strength. */
	void UpdateSize() const;

	/** The root component, used for physics simulation and collision. */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Components" )
	TObjectPtr<USphereComponent> SphereCollider;

	/** The visual representation of the pawn. Collision is disabled. */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Components" )
	TObjectPtr<UStaticMeshComponent> SphereMesh;

	/** An additional radius added to the collider to fine-tune the collision feel. */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (ClampMin = "0.0") )
	float ColliderRadiusThreshold = 1.f;

	/** The visual scale of the mesh when Strength is at its base value. */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (ClampMin = "0.0") )
	float BaseScale = 1.f;

	/** A multiplier for the force applied during movement. */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Stats" ) //meta advanced display
	float SpeedCoefficient = 10000.f;

	/** The pawn's current strength. Affects its size and ability to consume others. */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0.0") )
	float Strength = 1.f;

	/** The pawn's current speed stat. Used in force calculations. */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0.0") )
	float Speed = 1.f;
};
