// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/FTEnemyPawn.h"

#include "Components/SphereComponent.h"
#include "Pawns/FTPlayerPawn.h"

AFTEnemyPawn::AFTEnemyPawn()
{
	SphereCollider->SetCollisionProfileName( "Enemy" );
}

void AFTEnemyPawn::AttemptToConsume_Implementation( AFTPlayerPawn* PlayerPawn )
{
	// Helps to find Blueprints that don't override this function
	ensureMsgf( false,
	            TEXT("AttemptToConsume must be implemented in the Blueprint for class %s!"),
	            *GetClass()->GetName()
	);
}

void AFTEnemyPawn::EndPlay( const EEndPlayReason::Type EndPlayReason )
{
	Super::EndPlay( EndPlayReason );
	OnPawnDied.Broadcast( this );
}
