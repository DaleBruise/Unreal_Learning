// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LingLongCoinTestActor.generated.h"

class USceneComponent;

UCLASS()
class UNREALPROJECTS56_API ALingLongCoinTestActor : public AActor
{
	GENERATED_BODY()

public:
	
	ALingLongCoinTestActor();
	
	UFUNCTION(BlueprintCallable)
	void SpawnCoins(int32 SpawnCount);

protected:
	
	UPROPERTY(VisibleAnywhere, Category=Components)
	TObjectPtr<USceneComponent> DefaultSceneComp;
};
