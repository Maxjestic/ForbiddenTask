// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FTBasePawn.generated.h"

class USphereComponent;
/**
 * Base class for player and enemy spheres
 */
UCLASS( Abstract )
class FORBIDDENTASK_API AFTBasePawn : public APawn
{
	GENERATED_BODY()

public:
	AFTBasePawn();

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void Tick( float DeltaTime ) override;

	virtual void SetupPlayerInputComponent( UInputComponent* PlayerInputComponent ) override;

	FORCEINLINE float GetStrength() const { return Strength; };

protected:
	virtual void BeginPlay() override;
	
	void UpdateSize() const;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Components" )
	TObjectPtr<USphereComponent> SphereCollider;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Components" )
	TObjectPtr<UStaticMeshComponent> SphereMesh;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Components" )
	float ColliderRadiusThreshold = 1.f;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Stats" )
	float Strength = 500.0f;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Stats" )
	float Speed = 500.0f;
};
