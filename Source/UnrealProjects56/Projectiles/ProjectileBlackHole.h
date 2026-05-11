// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "ProjectileBlackHole.generated.h"

class URadialForceComponent;

UCLASS(Abstract)
class UNREALPROJECTS56_API AProjectileBlackHole : public AProjectileBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectileBlackHole();

	virtual void PostInitializeComponents() override;
	
protected:
	UPROPERTY(VisibleAnywhere, Category= "Components")
	TObjectPtr<URadialForceComponent> RadialForceComponent;

	UFUNCTION()
	void OnSphereOverlappedActor(UPrimitiveComponent* OverlappedComponent,
	                             AActor* OtherActor,
	                             UPrimitiveComponent* OtherComp,
	                             int32 OtherBodyIndex,
	                             bool bFromSweep,
	                             const FHitResult& SweepResult);
	
};
