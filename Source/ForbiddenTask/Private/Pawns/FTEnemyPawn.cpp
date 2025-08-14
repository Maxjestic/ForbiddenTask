// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/FTEnemyPawn.h"

#include "Components/SphereComponent.h"
#include "Pawns/FTPlayerPawn.h"

AFTEnemyPawn::AFTEnemyPawn()
{
	SphereCollider->SetCollisionProfileName( "Enemy" );
}

// check if it's possible if the implementation in BP exists
void AFTEnemyPawn::AttemptToConsume_Implementation( AFTPlayerPawn* PlayerPawn )
{
	UE_LOG(LogTemp, Error, TEXT("No implementation"));
}
