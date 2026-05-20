// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "LingLongAttributeSet.generated.h"

USTRUCT()
struct FLingLongAttribute
{
	GENERATED_BODY()
	
	FLingLongAttribute() {};
	FLingLongAttribute(float InValue) : Base(InValue) {};
	
	UPROPERTY(EditAnywhere)
	float Base = 0.0f;
	
	UPROPERTY(Transient)
	float Modifier = 0.0f;
	
	float GetValue() const;
	
};

UCLASS()
class UNREALPROJECTS56_API ULingLongAttributeSet : public UObject
{
	GENERATED_BODY()
};

UCLASS()
class UNREALPROJECTS56_API ULingLongHealthAttributeSet : public ULingLongAttributeSet
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, Category="Attributes")
	FLingLongAttribute Health;

	UPROPERTY(EditAnywhere, Category="Attributes")
	FLingLongAttribute MaxHealth;
	
	ULingLongHealthAttributeSet();
	
};
