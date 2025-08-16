// Copyright Maxjestic


#include "AI/Services/FTBTService_UpdateEngagement.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ForbiddenTask/FTLogChannels.h"

UFTBTService_UpdateEngagement::UFTBTService_UpdateEngagement()
{
	NodeName = TEXT( "Update Engagement" );
}

void UFTBTService_UpdateEngagement::TickNode( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds )
{
	Super::TickNode( OwnerComp, NodeMemory, DeltaSeconds );

	const APawn* PlayerPawn = Cast<APawn>(
		OwnerComp.GetBlackboardComponent()->GetValueAsObject( PlayerPawnKey.SelectedKeyName ) );
	const APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	if ( !PlayerPawn || !AIPawn )
	{
		return;
	}

	const float Distance = FVector::Dist( PlayerPawn->GetActorLocation(), AIPawn->GetActorLocation() );

	if ( OwnerComp.GetBlackboardComponent()->GetValueAsBool( IsEngagedKey.SelectedKeyName ) )
	{
		if ( Distance > LoseInterestRadius )
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool( IsEngagedKey.SelectedKeyName, false );
		}
	}
	else
	{
		if ( Distance < AwarenessRadius )
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool( IsEngagedKey.SelectedKeyName, true );
		}
	}
}
