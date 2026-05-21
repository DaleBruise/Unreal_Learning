// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickUp.h"

#include "SharedGameplayTags.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

#include "ActionSystem/ActionSystemLingLong.h"
#include "Core/LingLongGameplayStatics.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AHealthPickUp::AHealthPickUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->OverlapComp->SetCollisionProfileName("PickUps");

	this->PickUpMeshComp = this->CreateDefaultSubobject<UStaticMeshComponent>(
		TEXT("PickUpMeshComp"));
	this->PickUpMeshComp->SetCollisionProfileName("NoCollision");
	this->PickUpMeshComp->SetupAttachment(this->RootComponent);
}

void AHealthPickUp::OnActorOverlapped(UPrimitiveComponent* OverlappedComponent,
                                      AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp,
                                      int32 OtherBodyIndex,
                                      bool bFromSweep,
                                      const FHitResult& SweepResult)
{
	auto ActionComp = OtherActor->GetComponentByClass<UActionSystemLingLong>();

	if (ensure(ActionComp != nullptr) && !ULingLongGameplayStatics::IsFullHealth(ActionComp))
	{
		ActionComp->ApplyAttributeChange(
			SharedGameplayTags::Attribute_Health,
			this->HealingAmount,
			EAttributeModifiedType::Base);

		UGameplayStatics::PlaySoundAtLocation(this,
		                                      this->PickUpSound,
		                                      this->GetActorLocation(),
		                                      FRotator::ZeroRotator);

		this->Destroy();
	}
}
