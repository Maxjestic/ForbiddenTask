// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/FTPlayerPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/FTConsumable.h"

AFTPlayerPawn::AFTPlayerPawn()
{
	SphereCollider->SetCollisionProfileName( "Player" );
	SphereCollider->OnComponentBeginOverlap.AddDynamic( this, &AFTPlayerPawn::OnBeginOverlap );

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>( TEXT( "SpringArm" ) );
	SpringArm->SetupAttachment( RootComponent );
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>( TEXT( "Camera" ) );
	Camera->SetupAttachment( SpringArm, USpringArmComponent::SocketName );
	Camera->SetProjectionMode( ECameraProjectionMode::Orthographic );
	Camera->SetOrthoWidth( 4000.f );
}

void AFTPlayerPawn::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );
	if ( bHasMouseLocation )
	{
		const FVector ForceDirection = ( MouseLocation - GetActorLocation() ).GetSafeNormal2D();
		HandleMovement( ForceDirection );
	}
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

	UpdateSize();
}

void AFTPlayerPawn::AddToSpeed( const float& ToAdd )
{
	Speed += ToAdd;
	//TODO: Handle 0
}

void AFTPlayerPawn::AddToStrength( const float& ToAdd )
{
	Strength += ToAdd;
	//TODO: Handle 0

	UpdateSize();
}

void AFTPlayerPawn::OnBeginOverlap( UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                    const FHitResult& SweepResult )
{
	if ( IsValid( OtherActor ) && OtherActor->Implements<UFTConsumable>() )
	{
		IFTConsumable::Execute_AttemptToConsume( OtherActor, this );
	}
}
