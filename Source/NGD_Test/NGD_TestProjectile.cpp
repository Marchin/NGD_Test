// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "NGD_TestProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "PyramidElement.h"
#include "UnrealNetwork.h"


ANGD_TestProjectile::ANGD_TestProjectile()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	
	if (GetOwner())
	{
		CollisionComp->OnComponentHit.AddDynamic(this, &ANGD_TestProjectile::OnHit);		// set up a notification for when this component hits something blocking
	}
	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	bReplicates = true;
	bAlwaysRelevant = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void ANGD_TestProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		APyramidElement *const PyramidElement = Cast<APyramidElement>(OtherActor);
		if (PyramidElement)
		{
			PyramidElement->WasHit(Shooter, 1);
		}
		Destroy();
	}
}


void ANGD_TestProjectile::SetShooter(APlayerState* Player)
{
	Shooter = Player;
}

void ANGD_TestProjectile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);; 
	DOREPLIFETIME(ANGD_TestProjectile, ProjectileMovement);
}
