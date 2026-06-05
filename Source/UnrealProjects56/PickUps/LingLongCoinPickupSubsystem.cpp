// Fill out your copyright notice in the Description page of Project Settings.


#include "LingLongCoinPickupSubsystem.h"

#include "EngineUtils.h"
#include "LingLongTypes.h"
#include "UnrealProjects56.h"
#include "Player/LingLongChatacter.h"

void ULingLongCoinPickupSubsystem::AddCoinPickups(TArray<FVector> NewLocations, TArray<int32> NewAmounts)
{
	this->CoinLocations.Append(NewLocations);
	this->CoinAmounts.Append(NewAmounts);
}

void ULingLongCoinPickupSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	bool DebugFlag = CVarInteractionDebugDrawing.GetValueOnGameThread();

	/* Show the coins */
	auto* World = this->GetWorld();
	if (World != nullptr && DebugFlag)
	{
		for (int i = 0; i < this->CoinLocations.Num(); ++i)
		{
			DrawDebugPoint(World,
			               this->CoinLocations[i],
			               8.0f,
			               FColor::White);
		}
	}
	
	/* Pickup the coins and destroy them */
	FVector PLayerLocation = FVector::ZeroVector;
	for (const auto* PlayerCharacter : TActorRange<ALingLongCharacter>(World))
	{
		PLayerLocation = PlayerCharacter->GetActorLocation();	
	}
	
	// constexpr float PickupRadius = 200.0f;
	TArray<int32> ProcessList;
	for (int i = 0; i < this->CoinLocations.Num(); ++i)
	{
		float Dist = FVector::Dist(PLayerLocation, this->CoinLocations[i]);
		if (Dist < 200.0f)
		{
			ProcessList.Add(i);
		}
	}
	
	int32 TotalCoins = 0;
	for (int i = ProcessList.Num() - 1; i >= 0; --i)
	{
		int32 CoinAmountIndex = ProcessList[i];
		TotalCoins += this->CoinAmounts[CoinAmountIndex];
		
		this->RemoveCoinPickup(CoinAmountIndex);
	}
	
	if (DebugFlag)
		UE_LOG(LogGame, Log, TEXT("Picked up Coin Amount = %d"), TotalCoins);
	
}

TStatId ULingLongCoinPickupSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(LingLongCoinPickupSubsystem, STATGROUP_Tickables);
}

void ULingLongCoinPickupSubsystem::RemoveCoinPickup(const int32& IndexCoinRemove)
{
	this->CoinAmounts.RemoveAt(IndexCoinRemove);
	this->CoinLocations.RemoveAt(IndexCoinRemove);	 
}
