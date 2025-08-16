// Copyright Maxjestic


#include "AI/Tasks/FTBTTask_HandleAwareMovement.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Pawns/FTBasePawn.h"

FString UFTBTTask_HandleAwareMovement::GetStaticDescription() const
{
	switch ( AwareMovementMode )
	{
	case EFTAwareMovementMode::Flee:
		return FString::Printf( TEXT( "Flee from the Player" ) );
	case EFTAwareMovementMode::Chase:
		return FString::Printf( TEXT( "Chase the Player" ) );
	default:
		return FString::Printf( TEXT( "Unknown" ) );
	}
}

EBTNodeResult::Type UFTBTTask_HandleAwareMovement::ExecuteTask( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory )
{
	const AAIController* AIController = OwnerComp.GetAIOwner();
	if ( !AIController )
	{
		return EBTNodeResult::Failed;
	}

	AFTBasePawn* AIPawn = Cast<AFTBasePawn>( AIController->GetPawn() );
	if ( !AIPawn )
	{
		return EBTNodeResult::Failed;
	}

	const AFTBasePawn* PlayerPawn = Cast<AFTBasePawn>(
		OwnerComp.GetBlackboardComponent()->GetValueAsObject( PlayerPawnKey.SelectedKeyName ) );
	if ( !PlayerPawn )
	{
		return EBTNodeResult::Failed;
	}

	FVector MovementDirection;
	switch ( AwareMovementMode )
	{
	case EFTAwareMovementMode::Flee:
		MovementDirection = ( AIPawn->GetActorLocation() - PlayerPawn->GetActorLocation() ).GetSafeNormal2D();
		break;
	case EFTAwareMovementMode::Chase:
		MovementDirection = ( PlayerPawn->GetActorLocation() - AIPawn->GetActorLocation() ).GetSafeNormal2D();
		break;
	default:
		return EBTNodeResult::Failed;
	}
	AIPawn->HandleMovement( MovementDirection );
	return EBTNodeResult::Succeeded;
}
