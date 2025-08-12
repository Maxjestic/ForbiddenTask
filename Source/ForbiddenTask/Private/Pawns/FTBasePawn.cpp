// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/FTBasePawn.h"

AFTBasePawn::AFTBasePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	SetRootComponent(SphereMesh);

	SphereMesh->SetSimulatePhysics(true);
	SphereMesh->SetLinearDamping(2.0f);
}

void AFTBasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFTBasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFTBasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

