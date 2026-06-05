// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "LingLongCoinPickupSubsystem.generated.h"

class UInstancedStaticMeshComponent;
class UAudioComponent;
class ULingLongDeveloperSettings;

struct FPrimitiveInstanceId;

UCLASS()
class UNREALPROJECTS56_API ULingLongCoinPickupSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

protected:
	
	UPROPERTY()
	TObjectPtr<UInstancedStaticMeshComponent> WorldISM;
	
	UPROPERTY()
	TObjectPtr<UAudioComponent> WorldAudioComp;
	
	TArray<FVector> CoinLocations;
	TArray<int32> CoinAmounts;
	TArray<FPrimitiveInstanceId> MeshIDs;
	FName CoinPickupTriggerParameter; /*Cached from dev settings*/
	
	void OnPickupMeshLoadComplete(const FSoftObjectPath& SoftObjectPath, UObject* LoadedObject) const;
	void OnPickupSoundLoadComplete(const FSoftObjectPath& SoftObjectPath, UObject* LoadedObject) const;
	inline void PlayPickupSound() const;
	
public:
	
	void AddCoinPickups(TArray<FVector> NewLocations, TArray<int32> NewAmounts);
	void RemoveCoinPickup(const int32& IndexCoinRemove);
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
};
