// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGamePlayInterface.h"
#include "SItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class UNREAL_LEARNING_API ASItemChest : public AActor, public ISGamePlayInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float _target_pitch = .0f;

	void Interact_Implementation(APawn* InstigatorPawn);

public:	
	// Sets default values for this actor's properties
	ASItemChest();

protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* _base_mesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* _lid_mesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
