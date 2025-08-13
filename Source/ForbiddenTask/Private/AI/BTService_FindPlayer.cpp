// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_FindPlayer.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_FindPlayer::UBTService_FindPlayer()
{
	NodeName = TEXT( "Find Player" );
}

void UBTService_FindPlayer::TickNode( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds )
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
