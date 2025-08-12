// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/FTPlayerPawn.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/FTConsumable.h"

AFTPlayerPawn::AFTPlayerPawn()
{
	SphereMesh->OnComponentBeginOverlap.AddDynamic( this, &AFTPlayerPawn::OnOverlapBegin );
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>( TEXT("SpringArm") );
	SpringArm->SetupAttachment( RootComponent );
	SpringArm->TargetArmLength = 1000.f;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>( TEXT("Camera") );
	Camera->SetupAttachment( SpringArm, USpringArmComponent::SocketName );
	Camera->SetProjectionMode( ECameraProjectionMode::Orthographic );
}

void AFTPlayerPawn::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );
	if ( !bHasMouseLocation )
	{
		return;
	}
	const FVector ForceDirection = MouseLocation - GetActorLocation();
	SphereMesh->AddForce( ForceDirection.GetSafeNormal2D() * Speed );
}

void AFTPlayerPawn::SetTargetLocation( const FVector& NewTargetLocation )
{
	MouseLocation = NewTargetLocation;
	bHasMouseLocation = true;
}

void AFTPlayerPawn::StopMovement()
{
	MouseLocation = FVector::ZeroVector;
	bHasMouseLocation = false;
}

void AFTPlayerPawn::ChangeStats( const float& SpeedChange, const float& StrengthChange )
{
	Speed += SpeedChange;
	Strength += StrengthChange;
	//TODO: Handle case if either of stats is less than zero
	
	SphereMesh->SetWorldScale3D( FVector( Strength ) );
}

void AFTPlayerPawn::OnOverlapBegin( UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult )
{
	if (IsValid(OtherActor) && OtherActor->Implements<UFTConsumable>())
	{
		IFTConsumable::Execute_AttemptToConsume(OtherActor, this);
	}
}
