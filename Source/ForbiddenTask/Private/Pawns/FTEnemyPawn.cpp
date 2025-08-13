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
	if (!IsValid(PlayerPawn))
	{
		return;
	}

	if (StrengthToGive < 0.f || SpeedToGive < 0.f)
	{
		PlayerPawn->ChangeStats( SpeedToGive, StrengthToGive );
		Destroy();
		return;
	}
	
	if (PlayerPawn->GetStrength() > Strength)
	{
		PlayerPawn->ChangeStats( SpeedToGive, StrengthToGive );
	}
	else
	{
		PlayerPawn->ChangeStats( -SpeedToGive, -StrengthToGive );
	}
	
	Destroy();
}
