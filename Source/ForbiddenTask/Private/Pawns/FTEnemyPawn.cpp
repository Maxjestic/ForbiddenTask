// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/FTEnemyPawn.h"

#include "Pawns/FTPlayerPawn.h"

void AFTEnemyPawn::AttemptToConsume_Implementation( AFTPlayerPawn* PlayerPawn )
{
	if (!IsValid(PlayerPawn))
	{
		return;
	}
	
	if (PlayerPawn->GetStrength() > Strength)
	{
		UE_LOG(LogTemp, Warning, TEXT("Collided with something weaker!"));
		PlayerPawn->ChangeStats( SpeedToGive, StrengthToGive );
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Collided with something too strong!"));
		PlayerPawn->ChangeStats( -SpeedToGive, -StrengthToGive );
	}
	
	Destroy();
}
