// Copyright Maxjestic

#include "Core/FTAIController.h"

void AFTAIController::OnPossess( APawn* InPawn )
{
	Super::OnPossess( InPawn );

	if ( ensureMsgf(BehaviorTree, TEXT("Behavior Tree asset not assigned in %s!"), *GetName()) )
	{
		RunBehaviorTree( BehaviorTree );
	}
}
