// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "ActionSystemLingLong.generated.h"

struct FLingLongAttribute;

class ULingLongAction;
class ULingLongAttributeSet;


UENUM(BlueprintType)
enum EAttributeModifiedType
{
	Base,
	Modifier,
	OverrideBase,
	Invalid
};

/* 
 * Delegate是类型安全的函数指针包装器，是一种事件通知器
 * non-dynamic gives more performance
 * dynamic is for blueprint
*/
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChanged, 
	FGameplayTag /*AttributeTags*/, float /*NewAttributeValue*/, float /*OldAttributeValue*/ );

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnAttributeDynamicChanged, 
	FGameplayTag, AttributeTags, float, NewAttributeValue, float, OldAttributeValue );

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALPROJECTS56_API UActionSystemLingLong : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	TObjectPtr<ULingLongAttributeSet> Attributes;
	
	UPROPERTY(EditAnywhere, Category="Attributes", NoClear)
	TSubclassOf<ULingLongAttributeSet> AttributeSetClass;
	
	TMap<FGameplayTag, FOnAttributeChanged> AttributeListeners;
	
	TMap<FGameplayTag, TArray<FOnAttributeDynamicChanged>> AttributeDynamicListeners;
	
	TMap<FGameplayTag, FLingLongAttribute*> CachedAttributes;
	
	UPROPERTY()
	TArray<TObjectPtr<ULingLongAction>> Actions;

	UPROPERTY(EditAnywhere, Category="Actions")
	TArray<TSubclassOf<ULingLongAction>> DefaultActions;

public:
	UActionSystemLingLong();

	FGameplayTagContainer ActiveGameplayTags;
	
	UFUNCTION(BlueprintCallable)
	void ApplyAttributeChange(FGameplayTag AttributeTag, float Delta, EAttributeModifiedType ModifyType);
	
	UFUNCTION(BlueprintCallable, DisplayName="Add Attribute Listener", meta=(Keywords="events, delegate"))
	void AddDynamicAttributeChange(FOnAttributeDynamicChanged Event, FGameplayTag AttributeTag);

	UFUNCTION(BlueprintCallable, DisplayName="Remove Attribute Listener", meta=(Keywords="events, delegate"))
	void RemoveDynamicAttributeListener(FOnAttributeDynamicChanged Event);
	
	UFUNCTION(BlueprintCallable)
	float GetAttributeValue(FGameplayTag InAttributeTag) const;
	
	void StartAction(FGameplayTag InActionName);
	void StopAction(FGameplayTag InActionName);
	void GrantAction(TSubclassOf<ULingLongAction> NewActionClass);
	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;
	FLingLongAttribute* GetAttribute(FGameplayTag InAttributeTag) const;
	FOnAttributeChanged& GetAttributeListener(FGameplayTag AttributeTag);
};
