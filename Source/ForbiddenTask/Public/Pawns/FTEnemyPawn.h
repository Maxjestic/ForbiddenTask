// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/FTConsumable.h"
#include "Pawns/FTBasePawn.h"
#include "FTEnemyPawn.generated.h"

/**
 * 
 */
UCLASS()
class FORBIDDENTASK_API AFTEnemyPawn : public AFTBasePawn, public IFTConsumable
{
	GENERATED_BODY()

public:
	virtual void AttemptToConsume_Implementation(AFTPlayerPawn* PlayerPawn) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float StrengthToGive = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float SpeedToGive = 0.f;
};
