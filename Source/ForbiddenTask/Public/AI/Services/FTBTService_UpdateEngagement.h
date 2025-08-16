// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FTBTService_UpdateEngagement.generated.h"

/**
 * A BT Service that updates a boolean Blackboard key based on the AI distance to the player.
 * Uses two radii to create a hysteresis effect, preventing rapid state switching.
 */
UCLASS()
class FORBIDDENTASK_API UFTBTService_UpdateEngagement : public UBTService
{
	GENERATED_BODY()

public:
	/** Sets the default node name and update interval. */
	UFTBTService_UpdateEngagement();

protected:
	//~ Begin UBTAuxiliaryNode Interface
	virtual void TickNode( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds ) override;
	//~ End UBTAuxiliaryNode Interface

    /** The distance at which the AI will become engaged with the player. */
	UPROPERTY( EditAnywhere, Category="AI", meta = (ClampMin = "0.0") )
	float AwarenessRadius = 1500.f;

    /** The distance at which the AI will lose engagement. */
	UPROPERTY( EditAnywhere, Category="AI", meta = (ClampMin = "0.0") )
	float LoseInterestRadius = 3000.f;

	/** The Blackboard key to write the engagement status (bool) to. */
	UPROPERTY( EditAnywhere, Category="Blackboard" )
	FBlackboardKeySelector IsEngagedKey;

	/** The Blackboard key to read the Player Pawn from. */
	UPROPERTY( EditAnywhere, Category="Blackboard" )
	FBlackboardKeySelector PlayerPawnKey;

#if WITH_EDITOR
protected:
	/** Keeps LoseInterestRadius >= AwarenessRadius */
	virtual void PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent ) override;
#endif
};
