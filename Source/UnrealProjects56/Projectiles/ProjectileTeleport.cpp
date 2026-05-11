// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileTeleport.h"

#include "GameFramework/ProjectileMovementComponent.h"

#include "Components/AudioComponent.h"

#include "NiagaraComponent.h"

// Sets default values
AProjectileTeleport::AProjectileTeleport()
{
	this->MovementComp->InitialSpeed = 5000.0f;
}

void AProjectileTeleport::StartDelayedTeleport()
{
	this->PlayExplodeEffect();

	this->MovementComp->StopMovementImmediately();

	this->LoopedNiagaraComp->Deactivate();
	this->LoopedAudioComp->Stop();
	this->SetActorEnableCollision(false);

	// Another delay until we teleport (so player has a chance to see the VFX before we move them)
	this->GetWorldTimerManager().SetTimer(this->TeleportHandle,
	                                      this,
	                                      &ThisClass::HandleTeleportation,
	                                      this->TeleportSecondaryDelay);
}

void AProjectileTeleport::HandleTeleportation()
{
	APawn* ActorToTeleport = this->GetInstigator();

	check(ActorToTeleport);
	ActorToTeleport->TeleportTo(this->GetActorLocation(),
	                            ActorToTeleport->GetActorRotation());

	this->Destroy();
}

// Called when the game starts or when spawned
void AProjectileTeleport::BeginPlay()
{
	Super::BeginPlay();

	this->GetWorldTimerManager().SetTimer(this->TeleportHandle,
	                                this,
	                                &ThisClass::StartDelayedTeleport,
	                                this->DetonateDelay);
}

void AProjectileTeleport::OnActorHit(UPrimitiveComponent* HitComponent,
                                     AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp,
                                     FVector NormalImpulse,
                                     const FHitResult& Hit)
{
	this->GetWorldTimerManager().ClearTimer(this->TeleportHandle);

	this->StartDelayedTeleport();
}
