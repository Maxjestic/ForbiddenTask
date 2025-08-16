// Copyright Maxjestic

#include "AI/Services/FTBTService_FindPlayer.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UFTBTService_FindPlayer::UFTBTService_FindPlayer()
{
	NodeName = TEXT( "Find Player" );
}

void UFTBTService_FindPlayer::TickNode( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds )
{
	Super::TickNode( OwnerComp, NodeMemory, DeltaSeconds );

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn( GetWorld(), 0 );
	if ( !PlayerPawn )
	{
		OwnerComp.GetBlackboardComponent()->ClearValue( PlayerPawnKey.SelectedKeyName );
		return;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject( PlayerPawnKey.SelectedKeyName, PlayerPawn );
	
	//const APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	//if ( !AIPawn )
	//{
	//	return;
	//}
	//
	//const float Distance = FVector::Dist( PlayerPawn->GetActorLocation(), AIPawn->GetActorLocation() );
//
	//if ( OwnerComp.GetBlackboardComponent()->GetValueAsBool( IsEngagedKey.SelectedKeyName ) )
	//{
	//	if ( Distance > LoseInterestRadius )
	//	{
	//		OwnerComp.GetBlackboardComponent()->SetValueAsBool( IsEngagedKey.SelectedKeyName, false );
	//	}
	//}
	//else
	//{
	//	if ( Distance < AwarenessRadius )
	//	{
	//		OwnerComp.GetBlackboardComponent()->SetValueAsBool( IsEngagedKey.SelectedKeyName, true );
	//	}
	//}
}
