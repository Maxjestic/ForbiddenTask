// Copyright Maxjestic


#include "AI/Tasks/FTBTTask_HandleAwareMovement.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Pawns/FTBasePawn.h"

struct FHandleAwareMovementMemory
{
	TWeakObjectPtr<AFTBasePawn> AIPawn;
	TWeakObjectPtr<AFTBasePawn> PlayerPawn;
};

UFTBTTask_HandleAwareMovement::UFTBTTask_HandleAwareMovement()
{
	NodeName = TEXT( "Handle Aware of the Player Movement" );
	bNotifyTick = true;
}

FString UFTBTTask_HandleAwareMovement::GetStaticDescription() const
{
	switch ( AwareMovementMode )
	{
	case EFTAwareMovementMode::Flee:
		return FString::Printf( TEXT( "Flee from the Player" ) );
	case EFTAwareMovementMode::Chase:
		return FString::Printf( TEXT( "Chase the Player" ) );
	default:
		return FString::Printf( TEXT( "Unknown!" ) );
	}
}

uint16 UFTBTTask_HandleAwareMovement::GetInstanceMemorySize() const
{
	return sizeof( FHandleAwareMovementMemory );
}

EBTNodeResult::Type UFTBTTask_HandleAwareMovement::ExecuteTask( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory )
{
	const AAIController* AIController = OwnerComp.GetAIOwner();
	if ( !AIController )
	{
		return EBTNodeResult::Failed;
	}
	
	FHandleAwareMovementMemory* Memory = reinterpret_cast<FHandleAwareMovementMemory*>(NodeMemory);

	Memory->AIPawn = Cast<AFTBasePawn>( AIController->GetPawn() );
	if ( !Memory->AIPawn.IsValid() )
	{
		return EBTNodeResult::Failed;
	}

	const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if ( !BlackboardComp )
	{
		return EBTNodeResult::Failed;
	}

	Memory->PlayerPawn = Cast<AFTBasePawn>( BlackboardComp->GetValueAsObject( PlayerPawnKey.SelectedKeyName ) );
	if ( !Memory->PlayerPawn.IsValid() )
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::InProgress;
}

void UFTBTTask_HandleAwareMovement::TickTask( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds )
{
	Super::TickTask( OwnerComp, NodeMemory, DeltaSeconds );

	const FHandleAwareMovementMemory* Memory = reinterpret_cast<FHandleAwareMovementMemory*>(NodeMemory);

	if ( !Memory->AIPawn.IsValid() || !Memory->PlayerPawn.IsValid() )
	{
		FinishLatentTask( OwnerComp, EBTNodeResult::Failed );
		return;
	}

	FVector MovementVector;
	switch ( AwareMovementMode )
	{
	case EFTAwareMovementMode::Flee:
		MovementVector = ( Memory->AIPawn->GetActorLocation() - Memory->PlayerPawn->GetActorLocation() );
		break;
	case EFTAwareMovementMode::Chase:
		MovementVector = ( Memory->PlayerPawn->GetActorLocation() - Memory->AIPawn->GetActorLocation() );
		break;
	}

	Memory->AIPawn->HandleMovement( MovementVector.GetSafeNormal() );
}
