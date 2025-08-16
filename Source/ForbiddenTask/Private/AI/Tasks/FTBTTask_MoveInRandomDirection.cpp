// Copyright Maxjestic


#include "AI/Tasks/FTBTTask_MoveInRandomDirection.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Pawns/FTBasePawn.h"

UFTBTTask_MoveInRandomDirection::UFTBTTask_MoveInRandomDirection()
{
	NodeName = TEXT( "Move In Random Direction" );
	bNotifyTick = true;
}

EBTNodeResult::Type UFTBTTask_MoveInRandomDirection::ExecuteTask( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory )
{
	return EBTNodeResult::InProgress;
}

void UFTBTTask_MoveInRandomDirection::TickTask( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                                float DeltaSeconds )
{
	Super::TickTask( OwnerComp, NodeMemory, DeltaSeconds );

	AFTBasePawn* AIPawn = Cast<AFTBasePawn>( OwnerComp.GetAIOwner()->GetPawn() );
	if ( !AIPawn )
	{
		FinishLatentTask( OwnerComp, EBTNodeResult::Failed );
		return;
	}

	const FVector Direction = OwnerComp.GetBlackboardComponent()->GetValueAsVector( MoveDirectionKey.SelectedKeyName );
	AIPawn->HandleMovement( Direction );
}
