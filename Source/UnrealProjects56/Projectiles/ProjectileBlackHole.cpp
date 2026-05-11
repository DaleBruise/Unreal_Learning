// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBlackHole.h"

#include "PhysicsEngine/RadialForceComponent.h"

#include "Components/SphereComponent.h"

#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectileBlackHole::AProjectileBlackHole()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	this->RadialForceComponent = this->CreateDefaultSubobject<URadialForceComponent>(
		TEXT("RadialForceComponent"));
	this->RadialForceComponent->SetupAttachment(this->RootComponent);
	this->RadialForceComponent->ForceStrength = -800000.0f;
	this->RadialForceComponent->Radius = 1200.0f;
	this->RadialForceComponent->RemoveObjectTypeToAffect(
		UEngineTypes::ConvertToObjectType(ECC_Pawn));
	
	this->SphereComp->SetSphereRadius(20.0f);
	this->SphereComp->SetCollisionProfileName("BlackHoleCore");
	
	this->MovementComp->InitialSpeed = 500.0f;
	
	this->InitialLifeSpan = 5.0f; /* From Actor class*/
}

void AProjectileBlackHole::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	this->SphereComp->OnComponentBeginOverlap.AddDynamic(
		this, 
		&AProjectileBlackHole::OnSphereOverlappedActor);
}

void AProjectileBlackHole::OnSphereOverlappedActor(UPrimitiveComponent* OverlappedComponent,
                                                   AActor* OtherActor,
                                                   UPrimitiveComponent* OtherComp,
                                                   int32 OtherBodyIndex,
                                                   bool bFromSweep,
                                                   const FHitResult& SweepResult)
{
	if (OtherComp->IsSimulatingPhysics())
	{
		OtherActor->Destroy();
	}	
}
