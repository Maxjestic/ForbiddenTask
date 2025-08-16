// Copyright Maxjestic


#include "AI/Decorators/FTBTDecorator_CompareStrength.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Pawns/FTBasePawn.h"

FString UFTBTDecorator_CompareStrength::GetStaticDescription() const
{
	switch ( CompareMode )
	{
	case EFTDecoratorCompareMode::LessEqual:
		return FString::Printf( TEXT( "Am I weaker or equal?" ) );
	case EFTDecoratorCompareMode::Greater:
		return FString::Printf( TEXT( "Am I stronger?" ) );
	default:
		return FString::Printf( TEXT( "Unknown" ) );
	}
}

bool UFTBTDecorator_CompareStrength::CalculateRawConditionValue( UBehaviorTreeComponent& OwnerComp,
                                                                 uint8* NodeMemory ) const
{
	const AAIController* AIController = OwnerComp.GetAIOwner();
	if ( !AIController )
	{
		return false;
	}

	const AFTBasePawn* AIPawn = Cast<AFTBasePawn>( AIController->GetPawn() );
	if ( !AIPawn )
	{
		return false;
	}

	const AFTBasePawn* PlayerPawn = Cast<AFTBasePawn>(
		OwnerComp.GetBlackboardComponent()->GetValueAsObject( PlayerPawnKey.SelectedKeyName ) );
	if ( !PlayerPawn )
	{
		return false;
	}

	switch ( CompareMode )
	{
	case EFTDecoratorCompareMode::LessEqual:
		return AIPawn->GetStrength() <= PlayerPawn->GetStrength();
	case EFTDecoratorCompareMode::Greater:
		return AIPawn->GetStrength() > PlayerPawn->GetStrength();
	default:
		return false;
	}
}
