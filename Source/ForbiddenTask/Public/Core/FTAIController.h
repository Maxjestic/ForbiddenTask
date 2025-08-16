// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FTAIController.generated.h"

/**
 * AI Controller used for all enemies in the game
 * Runs the Behavior Tree that drives AI Logic
 */
UCLASS()
class FORBIDDENTASK_API AFTAIController : public AAIController
{
	GENERATED_BODY()

protected:
	//~ Begin AController Interface
	virtual void OnPossess(APawn* InPawn) override;
	//~ End AController Interface

    /** The Behavior Tree that defines AI logic */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
};
