// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "LingLongCoinPickupSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECTS56_API ULingLongCoinPickupSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

protected:
	
	TArray<FVector> CoinLocations;
	TArray<int32> CoinAmounts;
	
public:
	
	void AddCoinPickups(TArray<FVector> NewLocations, TArray<int32> NewAmounts);
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	void RemoveCoinPickup(const int32& IndexCoinRemove);
};
