// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FTAIController.generated.h"

/**
 * The primary AI Controller for all enemies.
 * Responsible for running the Behavior Tree that drives all logic.
 */
UCLASS()
class FORBIDDENTASK_API AFTAIController : public AAIController
{
	GENERATED_BODY()

protected:
	//~ Begin AController Interface
	virtual void OnPossess(APawn* InPawn) override;
	//~ End AController Interface

    /** The Behavior Tree asset to run when this controller possesses a pawn. */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
};
