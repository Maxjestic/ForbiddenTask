// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FTGameInstance.generated.h"

class UUserWidget;

/**
 * Game Instance class for this project
 * Stores classes for UI widgets used in the game
 * TODO: Add some checks for if the Subclasses are filled
 */
UCLASS()
class FORBIDDENTASK_API UFTGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	/** Play, Exit - simple logic */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	/** Bars representing Speed and Strength */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> HUDWidgetClass;

	/** Continue, Back to the Main Menu, pause gameplay */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> PauseMenuWidgetClass;

	/** Display Win/Lose, Play Again, Back to the Main Menu */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> EndScreenWidgetClass;
};
