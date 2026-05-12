// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePickUp.h"

#include "Components/SphereComponent.h"

ABasePickUp::ABasePickUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->OverlapComp = this->CreateDefaultSubobject<USphereComponent>(
		TEXT("OverlapComp"));
	this->OverlapComp->SetSphereRadius(128.0f);
	this->RootComponent = this->OverlapComp;
}

void ABasePickUp::OnActorOverlapped(UPrimitiveComponent* OverlappedComponent,
									  AActor* OtherActor,
									  UPrimitiveComponent* OtherComp,
									  int32 OtherBodyIndex,
									  bool bFromSweep,
									  const FHitResult& SweepResult)
{
}

void ABasePickUp::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	this->OverlapComp->OnComponentBeginOverlap.AddDynamic(this,
														  &ThisClass::OnActorOverlapped);
}
