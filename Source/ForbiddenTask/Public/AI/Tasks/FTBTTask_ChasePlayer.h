// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "FTBTTask_ChasePlayer.generated.h"

/**
 * Behavior Tree Task for chasing the Player
 */
UCLASS()
class FORBIDDENTASK_API UFTBTTask_ChasePlayer : public UBTTask_BlueprintBase
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
