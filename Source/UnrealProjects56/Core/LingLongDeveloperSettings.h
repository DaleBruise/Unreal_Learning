// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "LingLongDeveloperSettings.generated.h"

class UStaticMesh;

/**
 * 
 */
UCLASS(Config=Game, DefaultConfig)
class UNREALPROJECTS56_API ULingLongDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditDefaultsOnly, Category=Pickups)
	TSoftObjectPtr<UStaticMesh> CoinPickupMesh;
	
	UPROPERTY(Config, EditDefaultsOnly, Category=Pickups)
	TSoftObjectPtr<USoundBase> CoinPickupSound;
	
	UPROPERTY(Config, EditDefaultsOnly, Category=Pickups)
	FName CoinPickupTriggerParameter;
	
	virtual FName GetCategoryName() const override;
};
