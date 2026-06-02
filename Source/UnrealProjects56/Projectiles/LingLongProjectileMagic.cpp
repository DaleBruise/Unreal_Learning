// Fill out your copyright notice in the Description page of Project Settings.

#include "LingLongProjectileMagic.h"

#include "GameFramework/ProjectileMovementComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ALingLongProjectileMagic::ALingLongProjectileMagic()
{
	this->MovementComp->InitialSpeed = 2000.0f;

	this->InitialLifeSpan = 9.0f;
}

void ALingLongProjectileMagic::OnActorHit(UPrimitiveComponent* HitComponent,
                                          AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp,
                                          FVector NormalImpulse,
                                          const FHitResult& Hit)
{
	Super::OnActorHit(HitComponent,
	                  OtherActor,
	                  OtherComp,
	                  NormalImpulse,
	                  Hit);

	FVector HitFromDirection = this->GetActorRotation().Vector();

	UGameplayStatics::ApplyPointDamage(OtherActor,
	                                   10.0f,
	                                   HitFromDirection,
	                                   Hit,
	                                   this->GetInstigatorController(),
	                                   this,
	                                   this->DmgTypeClass);
}
