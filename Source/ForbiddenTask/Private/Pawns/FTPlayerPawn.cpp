// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/FTPlayerPawn.h"

void AFTPlayerPawn::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );
	if ( !bHasTargetLocation )
	{
		return;
	}
	const FVector ForceDirection = TargetLocation - GetActorLocation();
	SphereMesh->AddForce( ForceDirection.GetSafeNormal2D() * Speed );
}

void AFTPlayerPawn::SetTargetLocation( const FVector& NewTargetLocation )
{
	TargetLocation = NewTargetLocation;
	bHasTargetLocation = true;
}

void AFTPlayerPawn::StopMovement()
{
	TargetLocation = FVector::ZeroVector;
	bHasTargetLocation = false;
}
