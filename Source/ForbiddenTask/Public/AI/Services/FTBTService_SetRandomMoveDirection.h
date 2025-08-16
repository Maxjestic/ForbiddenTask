// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FTBTService_SetRandomMoveDirection.generated.h"

/**
 * Behavior Tree service used to set a random move direction
 */
UCLASS()
class FORBIDDENTASK_API UFTBTService_SetRandomMoveDirection : public UBTService
{
	GENERATED_BODY()
	
public:
	/**
	 * Default Constructor
	 * Sets Node Name
	 */
	UFTBTService_SetRandomMoveDirection();
	
protected:
	//~ Begin UBTAuxiliaryNode Interface
	virtual void TickNode( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds ) override;
	//~ End UBTAuxiliaryNode Interface

	/** Blackboard Key to avoid using string literals */
	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector MoveDirectionKey;
};
