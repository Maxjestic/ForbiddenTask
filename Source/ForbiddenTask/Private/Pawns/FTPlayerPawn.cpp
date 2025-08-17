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

void AFTPlayerPawn::SetStats( const float NewStrength, const float NewSpeed )
{
	Super::SetStats( NewStrength, NewSpeed );
	SpeedCheck();
	StrengthCheck();
}

void AFTPlayerPawn::AddSpeed( const float Value )
{
	Speed += FMath::Max( Value, 0.f );
	SpeedCheck();
}

void AFTPlayerPawn::AddStrength( const float Value )
{
	Strength += FMath::Max( Value, 0.f );
	StrengthCheck();
}

void AFTPlayerPawn::SubtractSpeed( const float Value )
{
	if ( bIsGodMode )
	{
		return;
	}
	Speed -= FMath::Max( Value, 0.f );
	SpeedCheck();
}

void AFTPlayerPawn::SubtractStrength( const float Value )
{
	if ( bIsGodMode )
	{
		return;
	}
	Strength -= FMath::Max( Value, 0.f );
	StrengthCheck();
}

void AFTPlayerPawn::AlterStats( const float StrengthDelta, const float SpeedDelta )
{
	if ( bIsGodMode )
	{
		GodModeAlterStats(StrengthDelta, SpeedDelta);
		return;
	}

	Strength += StrengthDelta;
	Speed += SpeedDelta;
	StrengthCheck();
	SpeedCheck();
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

bool AFTPlayerPawn::ToggleGodMode()
{
	bIsGodMode = !bIsGodMode;
	return bIsGodMode;
}

void AFTPlayerPawn::KillPlayer()
{
	bIsAlive = false;
	OnPawnDied.Broadcast( this );
}

void AFTPlayerPawn::GodModeAlterStats( const float StrengthDelta, const float SpeedDelta )
{
	if ( StrengthDelta > 0.f )
	{
		Strength += StrengthDelta;
		StrengthCheck();
	}
	else
	{
		FT_LOG_WARNING( TEXT("God Mode active, strength not changed.") );
	}
	if ( SpeedDelta > 0.f )
	{
		Speed += SpeedDelta;
		SpeedCheck();
	}
	else
	{
		FT_LOG_WARNING( TEXT("God Mode active, speed not changed.") );
	}
}
