// Copyright Maxjestic

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

void AFTPlayerPawn::AddSpeed( const float Value )
{
	Speed += Value;
	SpeedCheck();
}

void AFTPlayerPawn::AddStrength( const float Value )
{
	Strength += Value;
	StrengthCheck();
}

void AFTPlayerPawn::SubtractSpeed( const float Value )
{
	Speed -= Value;
	SpeedCheck();
}

void AFTPlayerPawn::SubtractStrength( const float Value )
{
	Strength -= Value;
	StrengthCheck();
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

void AFTPlayerPawn::StrengthCheck()
{
	Strength = FMath::Clamp( Strength, 0.f, MaxStrength );
	UpdateSize();
	OnStrengthChanged.Broadcast( Strength );
	if ( bIsAlive && Strength <= 0.f )
	{
		bIsAlive = false;
		FT_LOG_WARNING( TEXT("Player Pawn '%s' has died."), *GetName() );
		OnPawnDied.Broadcast( this );
	}
}

void AFTPlayerPawn::SpeedCheck()
{
	Speed = FMath::Clamp( Speed, 0.f, MaxSpeed );
	OnSpeedChanged.Broadcast( Speed );
	if ( bIsAlive && Speed <= 0.f )
	{
		bIsAlive = false;
		FT_LOG_WARNING( TEXT("Player Pawn '%s' has died."), *GetName() );
		OnPawnDied.Broadcast( this );
	}
}
