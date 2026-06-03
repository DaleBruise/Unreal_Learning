// Fill out your copyright notice in the Description page of Project Settings.


#include "LingLongCoinTestActor.h"

#include "NavigationSystem.h"
#include "PickUps/LingLongCoinPickupSubsystem.h"

ALingLongCoinTestActor::ALingLongCoinTestActor()
{
	this->DefaultSceneComp = 
		this->CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneComp"));
	this->RootComponent = this->DefaultSceneComp;
}

void ALingLongCoinTestActor::SpawnCoins(int32 SpawnCount)
{

	TArray<FVector> CoinLocations;
	TArray<int32> CoinAmounts;

	auto* NavSystem = UNavigationSystemV1::GetNavigationSystem(this);
	auto ActorLocation = this->GetActorLocation();
	for (int i = 0; i < SpawnCount; ++i)
	{
		FNavLocation NavLocation;
		NavSystem->GetRandomPointInNavigableRadius(
			ActorLocation,
			1024,
			NavLocation);
		
		CoinLocations.Add(NavLocation.Location);
		CoinAmounts.Add(5);
	}

	auto* CoinSystem =
		this->GetWorld()->GetSubsystem<ULingLongCoinPickupSubsystem>();
	CoinSystem->AddCoinPickups(CoinLocations, CoinAmounts);
}
