// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "FTBTTask_HandleAwareMovement.generated.h"

/** Defines the movement behavior for an AI that is aware of the player. */
UENUM( BlueprintType )
enum class EFTAwareMovementMode : uint8
{
	/** Move away from the player. */
	Flee,
	/** Move towards the player. */
	Chase
};

/**
 * A BT Task that continuously applies force to move the AI towards (Chase) or away from (Flee) the player.
 * The behavior is determined by the AwareMovementMode property.
 */
UCLASS()
class FORBIDDENTASK_API UFTBTTask_HandleAwareMovement : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

public:
	/** Sets the default node name and enables ticking. */
	UFTBTTask_HandleAwareMovement();

protected:
	//~ Begin UBTNode Interface	
	virtual FString GetStaticDescription() const override;
	virtual uint16 GetInstanceMemorySize() const override;
	//~ End UBTNode Interface

	//~ Begin UBTTask_BlueprintBase Interface
	virtual EBTNodeResult::Type ExecuteTask( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory ) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	//~ End UBTTask_BlueprintBase Interface

    /** The Blackboard key to read the Player Pawn from. */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Blackboard" )
	FBlackboardKeySelector PlayerPawnKey;

	/** Determines whether the AI should move towards or away from the player. */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Movement" )
	EFTAwareMovementMode AwareMovementMode = EFTAwareMovementMode::Flee;
};
