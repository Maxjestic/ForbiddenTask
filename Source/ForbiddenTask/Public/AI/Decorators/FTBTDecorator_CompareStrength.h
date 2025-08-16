// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "FTBTDecorator_CompareStrength.generated.h"

/**
 * Defines comparison logic for the strength decorator.
 */
UENUM( BlueprintType )
enum class EFTDecoratorCompareMode : uint8
{
	/** Condition passes if AI Strength is less than or equal to Player Strength. */
	LessEqual,
	/** Condition passes if AI Strength is greater than Player Strength. */
	Greater
};

/**
 * Compares the Strength of the AI pawn against the player's Strength.
 * The exact comparison logic is defined by the CompareMode enum.
 */
UCLASS()
class FORBIDDENTASK_API UFTBTDecorator_CompareStrength : public UBTDecorator
{
	GENERATED_BODY()
	
public:	
	/** Sets the default node name */
	UFTBTDecorator_CompareStrength();
	
protected:
	//~ Begin UBTNode Interface	
	virtual FString GetStaticDescription() const override;
	//~ End UBTNode Interface

	//~ Begin UBTDecorator Interface
	virtual bool CalculateRawConditionValue( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory ) const override;
	//~ End UBTDecorator Interface

    /** The Blackboard key for the Player Pawn to compare against. */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Blackboard" )
	FBlackboardKeySelector PlayerPawnKey;

	/** Defines how the AI strength is compared to the player. */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Compare" )
	EFTDecoratorCompareMode CompareMode = EFTDecoratorCompareMode::LessEqual;
};
