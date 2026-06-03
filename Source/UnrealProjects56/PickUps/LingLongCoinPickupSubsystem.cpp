// Fill out your copyright notice in the Description page of Project Settings.


#include "LingLongCoinPickupSubsystem.h"

#include "LingLongTypes.h"

void ULingLongCoinPickupSubsystem::AddCoinPickups(TArray<FVector> NewLocations, TArray<int32> NewAmounts)
{
	this->CoinLocations.Append(NewLocations);
	this->CoinAmounts.Append(NewAmounts);
}

void ULingLongCoinPickupSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto* World = this->GetWorld();
	if (World != nullptr 
		&& CVarInteractionDebugDrawing.GetValueOnGameThread())
	{
		for (int i = 0; i < this->CoinLocations.Num(); ++i)
		{
			DrawDebugPoint(World,
			               this->CoinLocations[i],
			               8.0f,
			               FColor::White);
		}
	}
}

TStatId ULingLongCoinPickupSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(LingLongCoinPickupSubsystem, STATGROUP_Tickables);
}
