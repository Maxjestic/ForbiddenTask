// Copyright Maxjestic

#include "Core/FTAIController.h"

void AFTAIController::OnPossess( APawn* InPawn )
{
	Super::OnPossess( InPawn );

	if ( BehaviorTree )
	{
		RunBehaviorTree( BehaviorTree );
	}
}
