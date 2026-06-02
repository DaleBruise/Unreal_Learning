// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileBase.h"

#include "GameFramework/ProjectileMovementComponent.h"

#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->SphereComp = this->CreateDefaultSubobject<USphereComponent>(
		TEXT("SphereComp"));
	this->SphereComp->SetSphereRadius(16.0f);
	this->SphereComp->SetCollisionProfileName("Projectile");
	this->RootComponent = this->SphereComp;

	this->MovementComp = this->CreateDefaultSubobject<UProjectileMovementComponent>(
		TEXT("MovementComp"));
	this->MovementComp->InitialSpeed = 2000.0f;
	this->MovementComp->ProjectileGravityScale = 0.0f;

	this->LoopedNiagaraComp = this->CreateDefaultSubobject<UNiagaraComponent>(
		TEXT("LoopedNiagaraComp"));
	this->LoopedNiagaraComp->SetupAttachment(this->SphereComp);

	this->LoopedAudioComp = this->CreateDefaultSubobject<UAudioComponent>(
		TEXT("LoopedAudioComp"));
	this->LoopedAudioComp->SetupAttachment(this->SphereComp);

	this->InitialLifeSpan = 30.0f;
}

void AProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent,
                                 AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp,
                                 FVector NormalImpulse,
                                 const FHitResult& Hit)
{
	this->PlayExplodeEffect();

	this->Destroy();
}

void AProjectileBase::PlayExplodeEffect() const
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,
	                                               this->ExplosionEffect,
	                                               this->GetActorLocation());

	UGameplayStatics::PlaySoundAtLocation(this,
	                                      this->ExplosionSound,
	                                      this->GetActorLocation(),
	                                      FRotator::ZeroRotator);
}

void AProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	this->SphereComp->OnComponentHit.AddDynamic(this,
	                                            &AProjectileBase::OnActorHit);

	this->SphereComp->IgnoreActorWhenMoving(this->GetInstigator(), true);
}
