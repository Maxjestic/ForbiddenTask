// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FTBTService_UpdateEngagement.generated.h"

/**
 * Behavior Tree Service used to set the engagement for AI
 */
UCLASS()
class FORBIDDENTASK_API UFTBTService_UpdateEngagement : public UBTService
{
	GENERATED_BODY()

public:
	/**
	 * Default Constructor
	 * Sets Node Name
	 */
	UFTBTService_UpdateEngagement();
	
protected:
	//~ Begin UBTAuxiliaryNode Interface
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	//~ End UBTAuxiliaryNode Interface

	/** Radius which triggers engagement */
	UPROPERTY(EditAnywhere, Category="AI")
	float AwarenessRadius = 1500.f;

	/** Radius which untriggers engagement */
	UPROPERTY(EditAnywhere, Category="AI")
	float LoseInterestRadius = 3000.f;

	/** Blackboard Key to avoid using string literals */
	UPROPERTY(EditAnywhere, Category="AI")
	FBlackboardKeySelector IsEngagedKey;
	
	/** Blackboard Key to avoid using string literals */
	UPROPERTY(EditAnywhere, Category="AI")
	FBlackboardKeySelector PlayerPawnKey;
};
