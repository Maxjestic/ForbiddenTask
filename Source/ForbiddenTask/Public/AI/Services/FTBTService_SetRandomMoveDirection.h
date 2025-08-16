// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FTBTService_SetRandomMoveDirection.generated.h"

/**
 * A BT Service that periodically calculates a new random direction
 * and stores it in a FVector Blackboard key.
 */
UCLASS()
class FORBIDDENTASK_API UFTBTService_SetRandomMoveDirection : public UBTService
{
	GENERATED_BODY()
	
public:
	/** Sets the default node name and update interval. */
	UFTBTService_SetRandomMoveDirection();
	
protected:
	//~ Begin UBTAuxiliaryNode Interface
	virtual void TickNode( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds ) override;
	//~ End UBTAuxiliaryNode Interface

    /** The Blackboard key to write the random FVector direction to. */
	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector MoveDirectionKey;
};
