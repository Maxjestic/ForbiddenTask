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
	virtual void Tick(float DeltaSeconds) override;
	
protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	void OnMoveTriggered();
	void OnMoveCompleted();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	TObjectPtr<UInputMappingContext> DefaultInputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input|Actions")
	TObjectPtr<UInputAction> MoveAction;

private:
	bool bIsButtonDown = false;
};
