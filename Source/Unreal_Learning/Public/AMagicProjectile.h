// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class UNREAL_LEARNING_API AAMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAMagicProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* _sphere_comp;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* _movement_comp;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* _effect_comp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
