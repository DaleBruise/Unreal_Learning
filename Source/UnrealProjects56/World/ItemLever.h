// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "ItemLever.generated.h"

class UStaticMeshComponent;


UCLASS()
class UNREALPROJECTS56_API AItemLever : public AActor, public IInteractionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItemLever();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BaseMeshComp;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> LeverMeshComp;
	
	UPROPERTY(EditAnywhere, Category = "Animation")
	float AnimSpeed = 50.0f;
	
	UPROPERTY(EditAnywhere, Category = "Animation")
	float AnimTargetPitch = 25.0f;
	
	float AnimCurrentPitch = -25.0f;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact_Implementation() override;
	
};
