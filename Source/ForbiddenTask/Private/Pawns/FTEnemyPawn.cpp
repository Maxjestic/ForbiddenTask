// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/FTEnemyPawn.h"

#include "Components/SphereComponent.h"
#include "Pawns/FTPlayerPawn.h"

AFTEnemyPawn::AFTEnemyPawn()
{
	SphereCollider->SetCollisionProfileName( "Enemy" );
}

void AFTEnemyPawn::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );
}

void AFTEnemyPawn::AttemptToConsume_Implementation( AFTPlayerPawn* PlayerPawn )
{
	UE_LOG(LogTemp, Error, TEXT("No implementation"));
}
