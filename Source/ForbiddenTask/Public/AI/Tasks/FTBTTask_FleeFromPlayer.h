// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "FTBTTask_FleeFromPlayer.generated.h"

/**
 * Behavior Tree Task for fleeing from Player
 */
UCLASS()
class FORBIDDENTASK_API UFTBTTask_FleeFromPlayer : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

protected:
	//~ Begin UBTTask_BlueprintBase Interface
	virtual EBTNodeResult::Type ExecuteTask( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory ) override;
	//~ End UBTTask_BlueprintBase Interface

	/** Blackboard Key to avoid using string literals */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Blackboard" )
	FBlackboardKeySelector PlayerPawnKey;
};
