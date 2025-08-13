// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_ChasePlayer.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Pawns/FTBasePawn.h"

EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory )
{
	const AAIController* AIController = OwnerComp.GetAIOwner();
	if ( !AIController ) return EBTNodeResult::Failed;

	AFTBasePawn* AIPawn = Cast<AFTBasePawn>( AIController->GetPawn() );
	if ( !AIPawn ) return EBTNodeResult::Failed;

	const AFTBasePawn* PlayerPawn = Cast<AFTBasePawn>(
		OwnerComp.GetBlackboardComponent()->GetValueAsObject( TEXT( "PlayerPawn" ) ) );
	if ( !PlayerPawn ) return EBTNodeResult::Failed;

	const FVector DirectionToPlayer = ( PlayerPawn->GetActorLocation() - AIPawn->GetActorLocation() ).GetSafeNormal2D();
	AIPawn->HandleMovement( DirectionToPlayer );

	return EBTNodeResult::Succeeded;
}
