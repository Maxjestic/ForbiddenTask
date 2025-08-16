// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FTPlayerController.generated.h"

class UFTGameInstance;
class AFTPlayerPawn;
class UInputAction;
class UInputMappingContext;

/**
 * The primary PlayerController for the game.
 * Handles player input for movement and UI interactions like pausing.
 */
UCLASS()
class FORBIDDENTASK_API AFTPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    /** Creates and displays the end-game UI widget. Called by the GameMode. */
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

    /** The default Input Mapping Context, containing all core input actions. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input" )
	TObjectPtr<UInputMappingContext> DefaultInputMappingContext;

    /** Input Action for player movement. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input|Actions" )
	TObjectPtr<UInputAction> MoveAction;

    /** Input Action for pausing the game. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input|Actions" )
	TObjectPtr<UInputAction> PauseAction;

private:
    /** Called continuously while the move input is active. */
	void OnMoveTriggered();

    /** Called once when the pause input is pressed. Toggles the pause state. */
	void OnPause();
	
    /** Creates the pause menu and pauses the game. */
	void HandlePause();

    /** Removes the pause menu and unpauses the game. */
	void HandleUnpause();
	
	/** Lazy loading for the Game Instance */
	UFTGameInstance* GetGameInstance();
	
	/** Cached ControlledPawn only for movement purposes */
	UPROPERTY()
	TObjectPtr<AFTPlayerPawn> ControlledPawn = nullptr;

	/** Cached GameInstance used for creating widgets */
	UPROPERTY()
	TObjectPtr<UFTGameInstance> CachedGameInstance = nullptr;

	/** Handle for Pause Menu Widget */
	UPROPERTY()
	TObjectPtr<UUserWidget> PauseMenu;
};
