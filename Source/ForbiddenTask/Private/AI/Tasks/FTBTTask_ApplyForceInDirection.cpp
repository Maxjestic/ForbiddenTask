// Copyright Maxjestic


#include "AI/Tasks/FTBTTask_ApplyForceInDirection.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Pawns/FTBasePawn.h"

struct FApplyForceTaskMemory
{
	TWeakObjectPtr<AFTBasePawn> AIPawn;
	TWeakObjectPtr<UBlackboardComponent> BlackboardComp;
};

UFTBTTask_ApplyForceInDirection::UFTBTTask_ApplyForceInDirection()
{
	NodeName = TEXT( "Apply Force In Direction" );
	bNotifyTick = true;
}

uint16 UFTBTTask_ApplyForceInDirection::GetInstanceMemorySize() const
{
	return sizeof( FApplyForceTaskMemory );
}

EBTNodeResult::Type UFTBTTask_ApplyForceInDirection::ExecuteTask( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory )
{
	const AAIController* AIController = OwnerComp.GetAIOwner();
	if ( !AIController )
	{
		return EBTNodeResult::Failed;
	}

	FApplyForceTaskMemory* Memory = reinterpret_cast<FApplyForceTaskMemory*>(NodeMemory);

	Memory->AIPawn = Cast<AFTBasePawn>( AIController->GetPawn() );
	if ( !Memory->AIPawn.IsValid() )
	{
		return EBTNodeResult::Failed;
	}

	Memory->BlackboardComp = OwnerComp.GetBlackboardComponent();
	if ( !Memory->BlackboardComp.IsValid() )
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::InProgress;
}

void UFTBTTask_ApplyForceInDirection::TickTask( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                                float DeltaSeconds )
{
	Super::TickTask( OwnerComp, NodeMemory, DeltaSeconds );

	const FApplyForceTaskMemory* Memory = reinterpret_cast<FApplyForceTaskMemory*>(NodeMemory);

	if ( !Memory->AIPawn.IsValid() || !Memory->BlackboardComp.IsValid() )
	{
		FinishLatentTask( OwnerComp, EBTNodeResult::Failed );
		return;
	}

	const FVector Direction = Memory->BlackboardComp->GetValueAsVector( MoveDirectionKey.SelectedKeyName );
	Memory->AIPawn->HandleMovement( Direction );
}
