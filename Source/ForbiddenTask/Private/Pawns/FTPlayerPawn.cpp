// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/FTPlayerPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "ForbiddenTask/FTLogChannels.h"
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

void AFTPlayerPawn::ChangeStats( const float SpeedChange, const float StrengthChange )
{
	Speed += SpeedChange;
	Strength += StrengthChange;
	//TODO: Handle case if either of stats is less than zero

	UpdateSize();
}

void AFTPlayerPawn::AddSpeed( const float Value )
{
	Speed += Value;
	//TODO: Handle 0
}

void AFTPlayerPawn::AddStrength( const float Value )
{
	Strength += Value;
	//TODO: Handle 0

	UpdateSize();
}

void AFTPlayerPawn::SubtractSpeed( const float Value )
{
	Speed -= Value;
	//TODO: Handle 0
}

void AFTPlayerPawn::SubtractStrength( const float Value )
{
	Strength -= Value;
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
