// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FTPlayerController.generated.h"

class UFTGameInstance;
class AFTPlayerPawn;
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

public:
	/** After Game Ends shows the Widget with proper text */
	void ShowEndScreen(const bool bPlayerWon);
	
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

	/** Callback for PauseAction Trigger Delegate */
	void OnPause();

	/** Default Input Mapping Context used by this controller to handle movement */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input" )
	TObjectPtr<UInputMappingContext> DefaultInputMappingContext;

	/** Move action that is responsible for triggering movement logic */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input|Actions" )
	TObjectPtr<UInputAction> MoveAction;

	/** Pause action that is responsible for triggering pause */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input|Actions" )
	TObjectPtr<UInputAction> PauseAction;

private:
	/** Creates HUDWidget and sets it up */
	void SetupHUDWidget();

	/** Lazy loading for the Game Instance */
	UFTGameInstance* GetGameInstance();
	
	/** Cached ControlledPawn only for movement purposes */
	UPROPERTY()
	TObjectPtr<AFTPlayerPawn> ControlledPawn = nullptr;

	/** Cached GameInstance used for creating widgets */
	UPROPERTY()
	TObjectPtr<UFTGameInstance> GameInstance = nullptr;
};
