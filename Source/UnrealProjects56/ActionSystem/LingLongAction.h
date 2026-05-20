// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "LingLongAction.generated.h"

struct FGameplayTag;


class UActionSystemLingLong;

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class UNREALPROJECTS56_API ULingLongAction : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, Category="Actions")
	void StartAction();
	
	UFUNCTION(BlueprintNativeEvent, Category="Actions")
	void StopAction();
	
	UFUNCTION(BlueprintCallable)
	UActionSystemLingLong* GetOwningComponent() const;
	
	FGameplayTag GetActionName() const;
	bool CanStart() const;
	bool IsRunning() const;
	float GetCoolDownTimeRemaining() const;
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category="Actions")
	FGameplayTag ActionName;
	
	UPROPERTY(Transient)
	float CoolDownUntil = 0.0f;
	
	UPROPERTY(EditDefaultsOnly, Category="Actions")
	float CoolDownTime = 0.0f;
	
	UPROPERTY(Transient)
	bool IsRunningFlag = false;
};
