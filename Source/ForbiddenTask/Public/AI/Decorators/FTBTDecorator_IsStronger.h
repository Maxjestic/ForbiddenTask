// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "FTBTDecorator_IsStronger.generated.h"

/**
 * Behavior Tree Decorator for calculating if the Enemy is stronger than Player
 */
UCLASS()
class FORBIDDENTASK_API UFTBTDecorator_IsStronger : public UBTDecorator
{
	GENERATED_BODY()

protected:
	//~ Begin UBTDecorator Interface
	virtual bool CalculateRawConditionValue( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory ) const override;
	//~ End UBTDecorator Interface

	/** Blackboard Key to avoid using string literals */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Blackboard" )
	FBlackboardKeySelector PlayerPawnKey;
};
