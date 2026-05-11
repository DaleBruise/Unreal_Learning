// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UNiagaraSystem;
class USphereComponent;
class UProjectileMovementComponent;
class UAudioComponent;
class USoundBase;
class UNiagaraComponent;

UCLASS(Abstract)
class UNREALPROJECTS56_API AProjectileBase : public AActor
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Component")
	TObjectPtr<USphereComponent> SphereComp;
	
	UPROPERTY(EditDefaultsOnly, Category = "Component")
	TObjectPtr<UProjectileMovementComponent> MovementComp;
	
	UPROPERTY(EditDefaultsOnly, Category = "Component")
	TObjectPtr<UNiagaraComponent> LoopedNiagaraComp;
	
	UPROPERTY(EditDefaultsOnly, Category = "Component")
	TObjectPtr<UAudioComponent> LoopedAudioComp;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<USoundBase> ExplosionSound;
	
	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent,
					AActor* OtherActor,
					UPrimitiveComponent* OtherComp,
					FVector NormalImpulse,
					const FHitResult& Hit);
	
	void PlayExplodeEffect() const;
	
public:
	// Sets default values for this actor's properties
	AProjectileBase();

	virtual void PostInitializeComponents() override;
	
};
