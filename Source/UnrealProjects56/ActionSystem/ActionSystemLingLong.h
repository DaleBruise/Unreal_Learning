// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionSystemLingLong.generated.h"

USTRUCT(BlueprintType)
struct FLingLongAttribute
{
	GENERATED_BODY()
	
	FLingLongAttribute() : Health(100.0f) {}
	
	UPROPERTY(BlueprintReadOnly)
	float Health;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChange, float, NewHealth, float, OldHealth);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALPROJECTS56_API UActionSystemLingLong : public UActorComponent
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FLingLongAttribute Attribute;

public:
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChange OnHealthChanged;
	
	UActionSystemLingLong();
	
	void ApplyHealthChange(float Value);
	
	
};
