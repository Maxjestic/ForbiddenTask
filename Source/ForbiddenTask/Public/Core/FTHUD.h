// Copyright Maxjestic

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FTHUD.generated.h"

class UFTHUDWidget;
/**
 * A base HUD class for Forbidden Task Project
 * Handles creation of HUDWidget
 */
UCLASS()
class FORBIDDENTASK_API AFTHUD : public AHUD
{
	GENERATED_BODY()

protected:
	//~ Begin AActor Interface
	virtual void BeginPlay() override;
	//~ Begin AActor Interface

	/** Reference for created HUD widget */
	UPROPERTY()
	TObjectPtr<UFTHUDWidget> HUDWidget;
};
