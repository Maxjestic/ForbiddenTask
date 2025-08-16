// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "FTBTDecorator_CompareStrength.generated.h"

/**
 * Defines compare logic modes for decorator
 */
UENUM( BlueprintType )
enum class EFTDecoratorCompareMode : uint8
{
	LessEqual,
	Greater
};

/**
 * Behavior Tree Decorator for strength check
 * Define Compare Mode
 */
UCLASS()
class FORBIDDENTASK_API UFTBTDecorator_CompareStrength : public UBTDecorator
{
	GENERATED_BODY()

protected:
	//~ Begin UBTNode Interface	
	virtual FString GetStaticDescription() const override;
	//~ End UBTNode Interface

	//~ Begin UBTDecorator Interface
	virtual bool CalculateRawConditionValue( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory ) const override;
	//~ End UBTDecorator Interface

	/** Blackboard Key to avoid using string literals */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Blackboard" )
	FBlackboardKeySelector PlayerPawnKey;

	/**
	 * Defines how the result will be calculated
	 * AI [LessEqual/Greater] Player
	 */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Compare" )
	EFTDecoratorCompareMode CompareMode = EFTDecoratorCompareMode::LessEqual;
};
