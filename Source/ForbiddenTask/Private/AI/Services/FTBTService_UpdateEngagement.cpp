// Copyright Maxjestic


#include "AI/Services/FTBTService_UpdateEngagement.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ForbiddenTask/FTLogChannels.h"

UFTBTService_UpdateEngagement::UFTBTService_UpdateEngagement()
{
	NodeName = TEXT( "Update Engagement" );
	Interval = 0.5f;
	RandomDeviation = 0.1f;
}

void UFTBTService_UpdateEngagement::TickNode( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds )
{
	Super::TickNode( OwnerComp, NodeMemory, DeltaSeconds );

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return;
	}
	
	const APawn* PlayerPawn = Cast<APawn>(
		OwnerComp.GetBlackboardComponent()->GetValueAsObject( PlayerPawnKey.SelectedKeyName ) );
	const APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	if ( !PlayerPawn || !AIPawn )
	{
		BlackboardComp->SetValueAsBool(IsEngagedKey.SelectedKeyName, false);
		return;
	}

	const float Distance = FVector::Dist( PlayerPawn->GetActorLocation(), AIPawn->GetActorLocation() );
	const bool bIsCurrentlyEngaged = BlackboardComp->GetValueAsBool(IsEngagedKey.SelectedKeyName);

	if ( bIsCurrentlyEngaged )
	{
		if ( Distance > LoseInterestRadius )
		{
			BlackboardComp->SetValueAsBool(IsEngagedKey.SelectedKeyName, false);
		}
	}
	else
	{
		if ( Distance < AwarenessRadius )
		{
			BlackboardComp->SetValueAsBool(IsEngagedKey.SelectedKeyName, true);
		}
	}
}

#if WITH_EDITOR
void UFTBTService_UpdateEngagement::PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent )
{
	Super::PostEditChangeProperty( PropertyChangedEvent );

	if ( LoseInterestRadius < AwarenessRadius )
	{
		LoseInterestRadius = AwarenessRadius;
	}
}
#endif // WITH_EDITOR
