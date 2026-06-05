// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "LingLongCoinPickupSubsystem.generated.h"

class UInstancedStaticMeshComponent;
struct FPrimitiveInstanceId;

UCLASS()
class UNREALPROJECTS56_API ULingLongCoinPickupSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

protected:
	
	UPROPERTY()
	TObjectPtr<UInstancedStaticMeshComponent> WorldISM;
	
	TArray<FVector> CoinLocations;
	TArray<int32> CoinAmounts;
	TArray<FPrimitiveInstanceId> MeshIDs;
	
public:
	
	void AddCoinPickups(TArray<FVector> NewLocations, TArray<int32> NewAmounts);
	void RemoveCoinPickup(const int32& IndexCoinRemove);
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
};
