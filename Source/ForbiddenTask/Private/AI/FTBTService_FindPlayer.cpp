// Copyright Maxjestic

#include "AI/FTBTService_FindPlayer.h"

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
}
