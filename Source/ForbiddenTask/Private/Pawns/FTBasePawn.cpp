// Fill out your copyright notice in the Description page of Project Settings.


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

void AFTBasePawn::BeginPlay()
{
	Super::BeginPlay();
}

void AFTBasePawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AFTBasePawn::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );
}

void AFTBasePawn::SetStats( const float& NewStrength, const float& NewSpeed )
{
	Strength = FMath::Clamp( NewStrength, 0.f, NewStrength );
	Speed = FMath::Clamp( NewSpeed, 0.f, NewSpeed );
	UpdateSize();
}

void AFTBasePawn::HandleMovement( const FVector& ForceDirection )
{
	SphereCollider->AddForce( ForceDirection * ( SpeedCoefficient / ( 1.f + Strength ) ) * Speed );
}

void AFTBasePawn::UpdateSize() const
{
	check( SphereCollider );
	if ( SphereMesh && SphereMesh->GetStaticMesh() )
	{
		SphereMesh->SetWorldScale3D( FVector( 1.f + Strength ) );
		const float MeshRadius = SphereMesh->GetStaticMesh()->GetBounds().SphereRadius;
		const float MeshScale = SphereMesh->GetComponentScale().GetAbs().GetMax();
		SphereCollider->SetSphereRadius( MeshRadius * MeshScale + ColliderRadiusThreshold );
	}
}
