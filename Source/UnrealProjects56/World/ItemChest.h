// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/InteractionInterface.h"
#include "ItemChest.generated.h"

class UStaticMeshComponent;
class UNiagaraSystem;

UCLASS()
class UNREALPROJECTS56_API AItemChest : public AActor, public IInteractionInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BaseMeshComp;
		
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> LidMeshComp;
	
	UPROPERTY(EditAnywhere, Category = "Animation")
	float AnimSpeed = 50.0f;
	
	UPROPERTY(EditAnywhere, Category = "Animation")
	float AnimTargetPitch = 120.0f;
	
	float AnimCurrentPitch = .0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TObjectPtr<UNiagaraSystem> TreasureBurstEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<USoundBase> TreasureBurstSound;
	
	void ChestAnimationComplete() const; //Definition is in the blueprint
	
	
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact() override;
	
	// Sets default values for this actor's properties
	AItemChest();

};
