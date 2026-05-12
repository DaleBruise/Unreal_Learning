// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickUp.generated.h"

class USphereComponent;

UCLASS(Abstract)
class UNREALPROJECTS56_API ABasePickUp : public AActor
{
	GENERATED_BODY()

public:
	virtual void PostInitializeComponents() override;

	ABasePickUp();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> OverlapComp;

	UFUNCTION()
	virtual void OnActorOverlapped(UPrimitiveComponent* OverlappedComponent,
								   AActor* OtherActor,
								   UPrimitiveComponent* OtherComp,
								   int32 OtherBodyIndex,
								   bool bFromSweep,
								   const FHitResult& SweepResult);
};
