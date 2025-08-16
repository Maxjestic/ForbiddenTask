// Copyright Maxjestic

#include "AI/Services/FTBTService_FindPlayer.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UFTBTService_FindPlayer::UFTBTService_FindPlayer()
{
	NodeName = TEXT( "Find Player" );
	Interval = 0.1f;
	RandomDeviation = 0.f;
}

void UFTBTService_FindPlayer::TickNode( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds )
{
	Super::TickNode( OwnerComp, NodeMemory, DeltaSeconds );
	
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return;
	}
	
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn( GetWorld(), 0 );
	const UObject* CurrentValue = BlackboardComp->GetValueAsObject(PlayerPawnKey.SelectedKeyName);

	if (CurrentValue != PlayerPawn)
	{
		BlackboardComp->SetValueAsObject(PlayerPawnKey.SelectedKeyName, PlayerPawn);
	}
}
