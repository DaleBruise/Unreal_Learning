// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveBarrel.h"
#include "NiagaraComponent.h"

#include "Components/AudioComponent.h"

#include "NiagaraFunctionLibrary.h"

#include "Kismet/GameplayStatics.h"

#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AExplosiveBarrel::AExplosiveBarrel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(
		TEXT("MeshComp"));
	this->MeshComp->SetSimulatePhysics(true);
	this->MeshComp->SetCollisionProfileName(TEXT("PhysicsActor"));
	this->MeshComp->SetCanEverAffectNavigation(false);
	this->RootComponent = this->MeshComp;

	this->RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(
		TEXT("RadialForceComp"));
	this->RadialForceComp->SetupAttachment(this->MeshComp);
	this->RadialForceComp->ImpulseStrength = 150000.0f;
	this->RadialForceComp->Radius = 800.0f;
	this->RadialForceComp->bAutoActivate = false;
	this->RadialForceComp->bIgnoreOwningActor = true;
	
}

void AExplosiveBarrel::Explode()
{
	this->bExploded = true;
	this->ActiveBurningEffectComp->Deactivate();
	this->ActiveBurningSoundComp->Stop();
	this->RadialForceComp->FireImpulse();
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		this, 
		this->ExplosionEffect, 
		this->GetActorLocation(), 
		this->GetActorRotation());
	
	UGameplayStatics::PlaySoundAtLocation(
		this, 
		this->ExplosionSound, 
		this->GetActorLocation(),
		FRotator::ZeroRotator);
}

float AExplosiveBarrel::TakeDamage(float DamageAmount,
                                   struct FDamageEvent const& DamageEvent,
                                   class AController* EventInstigator,
                                   AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// Allow exploding once, also skip when timer is already running
	if (bExploded || GetWorldTimerManager().TimerExists(ExplosionTimerHandle))
	{
		return ActualDamage;
	}

	// Hold onto both the Niagara and Audio Components to disable them during the Explode()

	this->ActiveBurningEffectComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
		this->BurningEffect,
		this->MeshComp,
		NAME_None,
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		EAttachLocation::Type::SnapToTarget,
		true);

	ActiveBurningSoundComp = UGameplayStatics::SpawnSoundAttached(
		this->BurningSound, 
		this->MeshComp);

	GetWorldTimerManager().SetTimer(
		ExplosionTimerHandle, 
		this,
		&AExplosiveBarrel::Explode, 
		ExplosionDelay);

	return ActualDamage;
}
