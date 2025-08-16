// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FTBasePawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPawnDiedSignature, AFTBasePawn*, DeadEnemy);

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

	/**
	 * Adds calculated Force in a given direction
	 * @param ForceDirection Direction in which force will be applied
	 */
	virtual void HandleMovement( const FVector& ForceDirection );
	
	FORCEINLINE float GetStrength() const { return Strength; };
	FORCEINLINE float GetSpeed() const { return Speed; };
	
	void SetStats(const float NewStrength, const float NewSpeed);

	FOnPawnDiedSignature OnPawnDied;

protected:
	//~ Begin AActor Interface
	virtual void OnConstruction( const FTransform& Transform ) override;
	//~ End AActor Interface
	
	/**
	 * Updates Scale of the SphereMesh after strength change and
	 * SphereCollider radius is updated accordingly
	 */
	void UpdateSize() const;

	/** Sphere Component used as Root, Collider and AddForce target */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Components" )
	TObjectPtr<USphereComponent> SphereCollider;

	/** SphereMesh used only as a visual representation */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Components" )
	TObjectPtr<UStaticMeshComponent> SphereMesh;

	/** Added to SphereCollider radius to make it more visible/responsive */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (ClampMin = "0.0") )
	float ColliderRadiusThreshold = 1.f;

	/** Base Scale for SphereMesh */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (ClampMin = "0.0") )
	float BaseScale = 1.f;

	/** Affects size and speed of the Pawn */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0.0") )
	float Strength = 1.f;

	/** Affects Speed and Handling when moving */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = "0.0") )
	float Speed = 1.f;

	/** Used to multiply Speed stat for AddForce to keep the Stats clearer */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Stats" ) //meta advanced display
	float SpeedCoefficient = 10000.f;
};
