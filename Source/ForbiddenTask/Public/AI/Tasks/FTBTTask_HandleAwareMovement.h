// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "FTBTTask_HandleAwareMovement.generated.h"

/*
 * Defines aware movement modes for the Task
 */
UENUM()
enum class EFTAwareMovementMode : uint8
{
	Flee,
	Chase
};

/**
 * Behavior Tree Task for handling movement of AI
 * When it's aware of the Player
 */
UCLASS()
class FORBIDDENTASK_API UFTBTTask_HandleAwareMovement : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

protected:
	//~ Begin UBTNode Interface	
	virtual FString GetStaticDescription() const override;
	//~ End UBTNode Interface

	//~ Begin UBTTask_BlueprintBase Interface
	virtual EBTNodeResult::Type ExecuteTask( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory ) override;
	//~ End UBTTask_BlueprintBase Interface

	/** Blackboard Key to avoid using string literals */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Blackboard" )
	FBlackboardKeySelector PlayerPawnKey;

	/**
	 * Defines how AI should move
	 * Flee - from the Player, Chase - to The Player
	 */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Movement" )
	EFTAwareMovementMode AwareMovementMode = EFTAwareMovementMode::Flee;
};
