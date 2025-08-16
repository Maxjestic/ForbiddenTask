// Copyright Maxjestic


#include "AI/Services/FTBTService_SetRandomMoveDirection.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "ForbiddenTask/FTLogChannels.h"

UFTBTService_SetRandomMoveDirection::UFTBTService_SetRandomMoveDirection()
{
	NodeName = TEXT( "Set Random Direction" );
	Interval = 4.0f;
	RandomDeviation = 0.5f;
}

void UFTBTService_SetRandomMoveDirection::TickNode( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                                    float DeltaSeconds )
{
	Super::TickNode( OwnerComp, NodeMemory, DeltaSeconds );
	
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return;
	}

	const float RandomAngle = FMath::FRandRange( 0.f, 360.f );
	const float AngleRadians = FMath::DegreesToRadians( RandomAngle );
	const FVector Direction = FVector( FMath::Cos( AngleRadians ), FMath::Sin( AngleRadians ), 0.f );

	BlackboardComp->SetValueAsVector( MoveDirectionKey.SelectedKeyName, Direction );
}
