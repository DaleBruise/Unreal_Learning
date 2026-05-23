// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "LingLongAttributeSet.generated.h"

class UActionSystemLingLong;

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

public:
	
	virtual void PostAttributeChanged() {};
	virtual void InitializeAttributes() {};
	UActionSystemLingLong* GetOwningComponent() const;
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
	
	virtual void PostAttributeChanged() override;
	
	ULingLongHealthAttributeSet();
	
};

UCLASS()
class ULingLongPawnAttributeSet : public ULingLongHealthAttributeSet
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category="Attributes")
	FLingLongAttribute MoveSpeed;
	
	ULingLongPawnAttributeSet();
	virtual void PostAttributeChanged() override;	
	virtual void InitializeAttributes() override;
	
private:
	
	void ApplyMoveSpeed();
};


UCLASS()
class ULingLongPlayerAttributeSet : public ULingLongPawnAttributeSet
{
	GENERATED_BODY()
	
public:
	
};

UCLASS()
class ULingLongMonsterAttributeSet : public ULingLongPawnAttributeSet
{
	GENERATED_BODY()
	
public:
	
	ULingLongMonsterAttributeSet();
	
};