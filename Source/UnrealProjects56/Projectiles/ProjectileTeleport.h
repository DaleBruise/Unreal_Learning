// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "ProjectileTeleport.generated.h"

UCLASS(Abstract)
class UNREALPROJECTS56_API AProjectileTeleport : public AProjectileBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectileTeleport();

protected:
	FTimerHandle TeleportHandle;

	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	float DetonateDelay = 0.2f;

	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	float TeleportSecondaryDelay = 0.2f;

	void StartDelayedTeleport();
	void HandleTeleportation();

	virtual void BeginPlay() override;
	virtual void OnActorHit(UPrimitiveComponent* HitComponent,
	                        AActor* OtherActor,
	                        UPrimitiveComponent* OtherComp,
	                        FVector NormalImpulse,
	                        const FHitResult& Hit) override;
};
