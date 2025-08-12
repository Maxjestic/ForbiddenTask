// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/FTBasePawn.h"
#include "FTPlayerPawn.generated.h"

/**
 * Player Class, handling movement
 */
UCLASS()
class FORBIDDENTASK_API AFTPlayerPawn : public AFTBasePawn
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaSeconds) override;
	void SetTargetLocation(const FVector& NewTargetLocation);
	void StopMovement();

private:
	FVector TargetLocation;
	bool bHasTargetLocation = false;
};
