// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FTConsumable.generated.h"

class AFTPlayerPawn;

UINTERFACE( MinimalAPI )
class UFTConsumable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for things that can be consumed by the Player
 */
class FORBIDDENTASK_API IFTConsumable
{
	GENERATED_BODY()

public:
	/**
	 * Called when the Player overlaps with anything that is Consumable
	 * @param PlayerPawn Allows affecting the Player
	 */
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Consumable" )
	void AttemptToConsume( AFTPlayerPawn* PlayerPawn );
};
