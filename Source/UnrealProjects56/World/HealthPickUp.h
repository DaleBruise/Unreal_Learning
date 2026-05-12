// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickUp.h"
#include "HealthPickUp.generated.h"

class UStaticMeshComponent;
class USoundBase;

UCLASS(Abstract)
class UNREALPROJECTS56_API AHealthPickUp : public ABasePickUp
{
	GENERATED_BODY()

public:
	
	AHealthPickUp();

protected:
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> PickUpMeshComp;
	
	UPROPERTY(EditDefaultsOnly, Category = "PickUp")
	TObjectPtr<USoundBase> PickUpSound;
	
	UPROPERTY(EditDefaultsOnly, Category = "PickUp")
	float HealingAmount = 25.0f;
	
	virtual void OnActorOverlapped(UPrimitiveComponent* OverlappedComponent,
	                               AActor* OtherActor,
	                               UPrimitiveComponent* OtherComp,
	                               int32 OtherBodyIndex,
	                               bool bFromSweep,
	                               const FHitResult& SweepResult) override;
};
