// Copyright Maxjestic

#include "Pawns/FTBasePawn.h"

#include "Components/SphereComponent.h"

AFTBasePawn::AFTBasePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollider = CreateDefaultSubobject<USphereComponent>( TEXT( "SphereCollider" ) );
	SetRootComponent( SphereCollider );
	SphereCollider->SetSimulatePhysics( true );
	SphereCollider->SetLinearDamping( 2.0f );
	SphereCollider->SetEnableGravity( false );

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "SphereMesh" ) );
	SphereMesh->SetupAttachment( RootComponent );
	SphereMesh->SetCollisionEnabled( ECollisionEnabled::NoCollision );
}

void AFTBasePawn::OnConstruction( const FTransform& Transform )
{
	Super::OnConstruction( Transform );
	UpdateSize();
}

void AFTBasePawn::SetStats( const float NewStrength, const float NewSpeed )
{
	Strength = FMath::Clamp( NewStrength, 0.f, NewStrength );
	Speed = FMath::Clamp( NewSpeed, 0.f, NewSpeed );
	UpdateSize();
}

void AFTBasePawn::HandleMovement( const FVector& ForceDirection )
{
	SphereCollider->AddForce( ForceDirection * ( SpeedCoefficient / ( BaseScale + Strength ) ) * Speed );
}

void AFTBasePawn::UpdateSize() const
{
	if ( SphereMesh->GetStaticMesh() )
	{
		SphereMesh->SetWorldScale3D( FVector( BaseScale + Strength ) );
		const float MeshRadius = SphereMesh->GetStaticMesh()->GetBounds().SphereRadius;
		const float MeshScale = SphereMesh->GetComponentScale().GetAbs().GetMax();
		SphereCollider->SetSphereRadius( MeshRadius * MeshScale + ColliderRadiusThreshold );
	}
}
