// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "FTBTDecorator_IsWeakerOrEqual.generated.h"

/**
 * Behavior Tree Decorator for calculating if the AI is weaker or equal to Player
 */
UCLASS()
class FORBIDDENTASK_API UFTBTDecorator_IsWeakerOrEqual : public UBTDecorator
{
	GENERATED_BODY()

protected:
	//~ Begin UBTDecorator Interface
	virtual bool CalculateRawConditionValue( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory ) const override;
	//~ End UBTDecorator Interface

	/** Blackboard Key to avoid using string literals */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Blackboard" )
	FBlackboardKeySelector PlayerPawnKey;

	//	AIMODULE_API virtual FString GetStaticDescription() const override; make it reusable with enum

};
