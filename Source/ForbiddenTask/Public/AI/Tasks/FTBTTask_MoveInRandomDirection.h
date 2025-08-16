// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "FTBTTask_MoveInRandomDirection.generated.h"

/**
 * Behavior Tree Task for applying force in a set random direction
 */
UCLASS()
class FORBIDDENTASK_API UFTBTTask_MoveInRandomDirection : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

public:	
	/**
	 * Default Constructor
	 * Sets Node Name
	 */
	UFTBTTask_MoveInRandomDirection();

protected:
	//~ Begin UBTTaskNode Interface
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	//~ End UBTTaskNode Interface

	/** Blackboard Key to avoid using string literals */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blackboard")
	FBlackboardKeySelector MoveDirectionKey;
};
