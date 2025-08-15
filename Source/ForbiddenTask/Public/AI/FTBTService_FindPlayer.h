// Fill out your copyright notice in the Description page of Project Settings.

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
	 * Default constructor
	 * Sets node name
	 */
	UFTBTService_FindPlayer();

protected:
	//~ Begin UBTAuxiliaryNode
	virtual void TickNode( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds ) override;
	//~ End UBTAuxiliaryNode

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Blackboard" )
	FBlackboardKeySelector PlayerPawnKey;
};
