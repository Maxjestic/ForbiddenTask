// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "FTBTTask_ApplyForceInDirection.generated.h"

/**
 * A BT Task that continuously applies force to the AI pawn
 * based on a direction read from the Blackboard.
 */
UCLASS()
class FORBIDDENTASK_API UFTBTTask_ApplyForceInDirection : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

public:	
    /** Sets the default node name and enables ticking. */
	UFTBTTask_ApplyForceInDirection();

protected:
	//~ Begin UBTNode Interface
	virtual uint16 GetInstanceMemorySize() const override;
	//~ End UBTNode Interface
	
	//~ Begin UBTTaskNode Interface
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	//~ End UBTTaskNode Interface
	
    /** The Blackboard key to read the movement direction from. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Blackboard")
	FBlackboardKeySelector MoveDirectionKey;
};
