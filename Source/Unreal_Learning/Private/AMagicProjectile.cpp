// Fill out your copyright notice in the Description page of Project Settings.


#include "AMagicProjectile.h"

#include "SAttributeComponent.h"
#include "Components/SphereComponent.h"

#include "GameFramework/ProjectileMovementComponent.h"

#include "Particles/ParticleSystemComponent.h"

// Sets default values
AAMagicProjectile::AAMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->_sphere_comp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	this->_sphere_comp->OnComponentBeginOverlap.AddDynamic(this, &AAMagicProjectile::OnActorOverlap);

	/* Set up a profile in UE GUI*/
	this->_sphere_comp->SetCollisionProfileName("Projectile"); 

	RootComponent = this->_sphere_comp;

	this->_movement_comp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	this->_movement_comp->InitialSpeed = 1000.f;
	this->_movement_comp->bRotationFollowsVelocity = true;
	this->_movement_comp->bInitialVelocityInLocalSpace = true;

	this->_effect_comp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	this->_effect_comp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AAMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this->GetInstigator())
	{
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(
			OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp != nullptr)
		{
			AttributeComp->ApplyHealthChange(-20.f);
			this->Destroy();
		}
	}
}
