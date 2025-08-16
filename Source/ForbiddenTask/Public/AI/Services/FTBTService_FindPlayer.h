// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FTBTService_FindPlayer.generated.h"

/**
 * A BT Service that periodically finds the player pawn and stores it in a Blackboard key.
 */
UCLASS()
class FORBIDDENTASK_API UFTBTService_FindPlayer : public UBTService
{
	GENERATED_BODY()

public:
	/** Sets the default node name and update interval. */
	UFTBTService_FindPlayer();

protected:
	//~ Begin UBTAuxiliaryNode Interface
	virtual void TickNode( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds ) override;
	//~ End UBTAuxiliaryNode Interface

	/** The Blackboard key to write the found Player Pawn to. */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Blackboard" )
	FBlackboardKeySelector PlayerPawnKey;
};
