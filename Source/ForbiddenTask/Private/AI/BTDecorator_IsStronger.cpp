// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_IsStronger.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Pawns/FTBasePawn.h"

bool UBTDecorator_IsStronger::CalculateRawConditionValue( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory ) const
{
	const AAIController* AIController = OwnerComp.GetAIOwner();
	if ( !AIController ) return false;

	const AFTBasePawn* AIPawn = Cast<AFTBasePawn>( AIController->GetPawn() );
	if ( !AIPawn ) return false;

	const AFTBasePawn* PlayerPawn = Cast<AFTBasePawn>(
		OwnerComp.GetBlackboardComponent()->GetValueAsObject( TEXT( "PlayerPawn" ) ) );
	if ( !PlayerPawn ) return false;

	return AIPawn->GetStrength() > PlayerPawn->GetStrength();
}
