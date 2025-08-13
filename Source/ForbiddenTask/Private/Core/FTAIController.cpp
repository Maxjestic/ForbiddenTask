// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/FTAIController.h"

void AFTAIController::OnPossess( APawn* InPawn )
{
	Super::OnPossess( InPawn );

	if (BehaviorTree)
	{
		RunBehaviorTree( BehaviorTree );
	}
}
