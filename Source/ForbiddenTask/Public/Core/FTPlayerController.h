// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FTPlayerController.generated.h"

class AFTBasePawn;
class UInputAction;
class UInputMappingContext;

/**
 * Base class for PlayerController in the ForbiddenTask project
 * Handles Movement - When mouse button pressed player should follow the mouse
 */
UCLASS()
class FORBIDDENTASK_API AFTPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	//~ Begin AActor Interface
	virtual void BeginPlay() override;
	//~ End AActor Interface
	
	//~ Begin APlayerController Interface
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	//~ Begin APlayerController Interface

	/** Callback for MoveAction Trigger Delegate */
	void OnMoveTriggered();

	/** Default Input Mapping Context used by this controller to handle movement */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input" )
	TObjectPtr<UInputMappingContext> DefaultInputMappingContext;

	/** Move action that is responsible for triggering movement logic */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input|Actions" )
	TObjectPtr<UInputAction> MoveAction;

private:
	/** Cached ControlledPawn only for movement purposes */
	UPROPERTY()
	TObjectPtr<AFTBasePawn> ControlledPawn;
};
