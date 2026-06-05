// Fill out your copyright notice in the Description page of Project Settings.


#include "LingLongCoinPickupSubsystem.h"
#include "EngineUtils.h"
#include "LingLongTypes.h"
#include "UnrealProjects56.h"

#include "Components/AudioComponent.h"
#include "Components/InstancedStaticMeshComponent.h"

#include "Core/LingLongDeveloperSettings.h"

#include "Player/LingLongChatacter.h"

void ULingLongCoinPickupSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	UWorld* World = this->GetWorld();
	this->WorldISM =
		NewObject<UInstancedStaticMeshComponent>(World,
		                                         NAME_None,
		                                         RF_Transient);
	this->WorldISM->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	this->WorldISM->SetAffectDistanceFieldLighting(false);
	this->WorldISM->RegisterComponentWithWorld(World);

	const auto DevSettings = GetDefault<ULingLongDeveloperSettings>();

	FLoadSoftObjectPathAsyncDelegate Delegate;
	Delegate.BindUObject(this, &ThisClass::OnPickupMeshLoadComplete);
	int32 ID = DevSettings->CoinPickupMesh.LoadAsync(Delegate);
	DevSettings->CoinPickupSound.LoadAsync(
		FLoadSoftObjectPathAsyncDelegate::CreateUObject(this, &ThisClass::OnPickupSoundLoadComplete));
	this->CoinPickupTriggerParameter = DevSettings->CoinPickupTriggerParameter;

	this->WorldAudioComp = NewObject<UAudioComponent>(World, NAME_None, RF_Transient);
	this->WorldAudioComp->SetAutoActivate(false);
	this->WorldAudioComp->bAllowSpatialization = false;
	this->WorldAudioComp->RegisterComponentWithWorld(World);
}

void ULingLongCoinPickupSubsystem::OnPickupMeshLoadComplete(
	const FSoftObjectPath& SoftObjectPath,
	UObject* LoadedObject) const
{
	this->WorldISM->SetStaticMesh(Cast<UStaticMesh>(LoadedObject));
}

void ULingLongCoinPickupSubsystem::OnPickupSoundLoadComplete(
	const FSoftObjectPath& SoftObjectPath,
	UObject* LoadedObject) const
{
	this->WorldAudioComp->SetSound(Cast<USoundBase>(LoadedObject));
}

inline void ULingLongCoinPickupSubsystem::PlayPickupSound() const
{
	if (!this->WorldAudioComp->IsPlaying())
	{
		this->WorldAudioComp->Play();
	}
	this->WorldAudioComp->SetTriggerParameter(this->CoinPickupTriggerParameter);
}

void ULingLongCoinPickupSubsystem::Tick(float DeltaTime)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(LingLongCoinPickupSubsystem::Tick);

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

	TArray<int32> ProcessList;
	{
		TRACE_CPUPROFILER_EVENT_SCOPE(LingLongCoinPickupSubsystem::Tick::CoinDistanceCalc);

		for (int i = 0; i < this->CoinLocations.Num(); ++i)
		{
			float Dist = FVector::Dist(PLayerLocation, this->CoinLocations[i]);
			if (Dist < 200.0f)
			{
				ProcessList.Add(i);
			}
		}
	}

	int32 TotalCoins = 0;
	{
		TRACE_CPUPROFILER_EVENT_SCOPE(LingLongCoinPickupSubsystem::Tick::HandlePickups);

		for (int i = ProcessList.Num() - 1; i >= 0; --i)
		{
			int32 CoinAmountIndex = ProcessList[i];
			TotalCoins += this->CoinAmounts[CoinAmountIndex];

			this->RemoveCoinPickup(CoinAmountIndex);
		}
		if (TotalCoins > 0)
		{
			PlayPickupSound();
		}
	}

	if (DebugFlag)
		UE_LOG(LogGame, Log, TEXT("Picked up Coin Amount = %d"), TotalCoins);
}

TStatId ULingLongCoinPickupSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(LingLongCoinPickupSubsystem, STATGROUP_Tickables);
}

void ULingLongCoinPickupSubsystem::AddCoinPickups(TArray<FVector> NewLocations, TArray<int32> NewAmounts)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(LingLongCoinPickupSubsystem::AddCoinPickups);

	this->CoinLocations.Append(NewLocations);
	this->CoinAmounts.Append(NewAmounts);

	TArray<FTransform> MeshTransforms;
	for (const auto& Location : NewLocations)
	{
		MeshTransforms.Add(FTransform(Location
			+ FVector(0, 0, 50.0f)));
	}

	auto NewMeshIDs =
		this->WorldISM->AddInstancesById(MeshTransforms, true, false);
	this->MeshIDs.Append(NewMeshIDs);
}

void ULingLongCoinPickupSubsystem::RemoveCoinPickup(const int32& IndexCoinRemove)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(LingLongCoinPickupSubsystem::RemoveCoinPickup);

	this->CoinAmounts.RemoveAtSwap(IndexCoinRemove, EAllowShrinking::No);
	this->CoinLocations.RemoveAtSwap(IndexCoinRemove, EAllowShrinking::No);

	this->WorldISM->RemoveInstanceById(this->MeshIDs[IndexCoinRemove]);
	this->MeshIDs.RemoveAtSwap(IndexCoinRemove, EAllowShrinking::No);
}
