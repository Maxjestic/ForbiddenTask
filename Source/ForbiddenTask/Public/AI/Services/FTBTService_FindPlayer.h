// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FTBTService_FindPlayer.generated.h"

/**
 * Behavior Tree Service for finding the Player
 */
UCLASS()
class FORBIDDENTASK_API UFTBTService_FindPlayer : public UBTService
{
	GENERATED_BODY()

public:
	/**
	 * Default Constructor
	 * Sets Node Name
	 */
	UFTBTService_FindPlayer();

protected:
	//~ Begin UBTAuxiliaryNode Interface
	virtual void TickNode( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds ) override;
	//~ End UBTAuxiliaryNode Interface

	/** Blackboard Key to avoid using string literals */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Blackboard" )
	FBlackboardKeySelector PlayerPawnKey;
};
