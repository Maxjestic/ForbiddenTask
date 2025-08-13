// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FTBasePawn.generated.h"

class USphereComponent;

/**
 * AFTBasePawn serves as the base class for pawns in the ForbiddenTask project.
 */
UCLASS( Abstract, NotBlueprintable )
class FORBIDDENTASK_API AFTBasePawn : public APawn
{
	GENERATED_BODY()

public:
	/**
	 * Default constructor
	 * Sets up Sphere and StaticMesh components
	 */
	AFTBasePawn();

	//~ Begin AActor Interface
	virtual void OnConstruction( const FTransform& Transform ) override;
	virtual void Tick( float DeltaTime ) override;
	//~ End AActor Interface

	//~ Begin APawn Interface
	virtual void SetupPlayerInputComponent( UInputComponent* PlayerInputComponent ) override;
	//~ End APawn Interface

	FORCEINLINE float GetStrength() const { return Strength; };

	/**
	 * Adds calculated Force in a given direction
	 * @param ForceDirection Direction in which force will be applied
	 */
	virtual void HandleMovement( const FVector& ForceDirection );

protected:
	//~ Begin AActor Interface
	virtual void BeginPlay() override;
	//~ End AActor Interface

	/**
	 * Updates Scale of the SphereMesh after strength change and
	 * SphereCollider radius is updated accordingly
	 */
	void UpdateSize() const;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Components" )
	TObjectPtr<USphereComponent> SphereCollider;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Components" )
	TObjectPtr<UStaticMeshComponent> SphereMesh;

	// Added to SphereCollider radius to make it more visible/responsive
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (ClampMin = "0.0") )
	float ColliderRadiusThreshold = 1.f;

	// Affects size and speed of the Pawn
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0.1") )
	float Strength = 1.f;

	// Affects Speed and Handling when moving
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0.1") )
	float Speed = 1.f;

	/**
	 * Used to multiply Speed stat for AddForce to keep the Stats clearer
	 * Force = Direction * Speed / Strength * Coefficient
	 */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Stats" )
	float SpeedCoefficient = 10000.f;
};
