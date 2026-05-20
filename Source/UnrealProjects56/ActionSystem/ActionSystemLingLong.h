// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "ActionSystemLingLong.generated.h"

class ULingLongAction;
class ULingLongAttributeSet;

// USTRUCT(BlueprintType)
// struct FLingLongAttribute
// {
// 	GENERATED_BODY()
//
// 	FLingLongAttribute() : Health(100.0f), HealthMax(100.0f)
// 	{
// 	}
//
// 	UPROPERTY(BlueprintReadOnly)
// 	float Health;
//
// 	UPROPERTY(BlueprintReadOnly)
// 	float HealthMax;
// };

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChange, float, NewHealth, float, OldHealth);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALPROJECTS56_API UActionSystemLingLong : public UActorComponent
{
	GENERATED_BODY()

protected:
	// UPROPERTY(BlueprintReadOnly, Category="Attributes")
	// FLingLongAttribute Attribute;

	UPROPERTY()
	TObjectPtr<ULingLongAttributeSet> Attributes;
	
	UPROPERTY(EditAnywhere, Category="Attributes", NoClear)
	TSubclassOf<ULingLongAttributeSet> AttributeSetClass;
	
	UPROPERTY()
	TArray<TObjectPtr<ULingLongAction>> Actions;

	UPROPERTY(EditAnywhere, Category="Actions")
	TArray<TSubclassOf<ULingLongAction>> DefaultActions;

public:
	UActionSystemLingLong();

	UPROPERTY(BlueprintAssignable)
	FOnHealthChange OnHealthChanged;

	FGameplayTagContainer ActiveGameplayTags;
	
	bool IsFullHealth() const;
	float GetHealth() const;
	float GetHealthMax() const;
	void ApplyHealthChange(float Value);
	void StartAction(FGameplayTag InActionName);
	void StopAction(FGameplayTag InActionName);
	void GrantAction(TSubclassOf<ULingLongAction> NewActionClass);
	virtual void InitializeComponent() override;
};
