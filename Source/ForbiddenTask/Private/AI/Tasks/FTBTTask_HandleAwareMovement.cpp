// Copyright Maxjestic


#include "AI/Tasks/FTBTTask_HandleAwareMovement.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ForbiddenTask/FTLogChannels.h"
#include "Pawns/FTBasePawn.h"

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

EBTNodeResult::Type UFTBTTask_HandleAwareMovement::ExecuteTask( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory )
{
	return EBTNodeResult::InProgress;
}

void UFTBTTask_HandleAwareMovement::TickTask( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds )
{
	Super::TickTask( OwnerComp, NodeMemory, DeltaSeconds );

	const AAIController* AIController = OwnerComp.GetAIOwner();
	if ( !AIController )
	{
		FT_LOG_WARNING( TEXT("AIController nullptr!") )
		FinishLatentTask( OwnerComp, EBTNodeResult::Failed );
		return;
	}

	AFTBasePawn* AIPawn = Cast<AFTBasePawn>( AIController->GetPawn() );
	if ( !AIPawn )
	{
		FT_LOG_WARNING( TEXT("AIPawn nullptr!") )
		FinishLatentTask( OwnerComp, EBTNodeResult::Failed );
		return;
	}

	const AFTBasePawn* PlayerPawn = Cast<AFTBasePawn>(
		OwnerComp.GetBlackboardComponent()->GetValueAsObject( PlayerPawnKey.SelectedKeyName ) );
	if ( !PlayerPawn )
	{
		FT_LOG_WARNING( TEXT("PlayerPawn nullptr!") )
		FinishLatentTask( OwnerComp, EBTNodeResult::Failed );
		return;
	}

	FVector MovementVector;
	switch ( AwareMovementMode )
	{
	case EFTAwareMovementMode::Flee:
		MovementVector = ( AIPawn->GetActorLocation() - PlayerPawn->GetActorLocation() );
		break;
	case EFTAwareMovementMode::Chase:
		MovementVector = ( PlayerPawn->GetActorLocation() - AIPawn->GetActorLocation() );
		break;
	default:
		FT_LOG_WARNING( TEXT("Unknown AwareMovementMode!") )
		FinishLatentTask( OwnerComp, EBTNodeResult::Failed );
		return;
	}
	AIPawn->HandleMovement( MovementVector.GetSafeNormal2D() );
}
