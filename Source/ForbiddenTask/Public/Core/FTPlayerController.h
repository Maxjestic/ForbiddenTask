// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FTPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;

/**
 * Base class for PlayerController in the ForbiddenTask project
 */
UCLASS()
class FORBIDDENTASK_API AFTPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	//~ Begin AActor Interface
	virtual void Tick( float DeltaSeconds ) override;
	//~ End AActor Interface

protected:
	//~ Begin APlayerController Interface
	virtual void SetupInputComponent() override;
	//~ Begin APlayerController Interface

	//~ Begin AActor Interface
	virtual void BeginPlay() override;
	//~ End AActor Interface

	//~ Begin Handling Input
	void OnMoveTriggered();
	void OnMoveCompleted();
	//~ End Handling Input

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input" )
	TObjectPtr<UInputMappingContext> DefaultInputMappingContext;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input|Actions" )
	TObjectPtr<UInputAction> MoveAction;

private:
	bool bIsButtonDown = false;
};
