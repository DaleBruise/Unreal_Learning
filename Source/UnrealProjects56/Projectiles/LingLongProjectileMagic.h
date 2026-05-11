// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "LingLongProjectileMagic.generated.h"

class UDamageType;

UCLASS(Abstract)
class UNREALPROJECTS56_API ALingLongProjectileMagic : public AProjectileBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALingLongProjectileMagic();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UDamageType> DmgTypeClass;

	virtual void OnActorHit(UPrimitiveComponent* HitComponent,
	                        AActor* OtherActor,
	                        UPrimitiveComponent* OtherComp,
	                        FVector NormalImpulse,
	                        const FHitResult& Hit) override;
};
