// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "ActionSystemLingLong.generated.h"

struct FLingLongAttribute;

class ULingLongAction;
class ULingLongAttributeSet;


UENUM()
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
*/
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChanged, 
	FGameplayTag /*AttributeTags*/, float /*NewAttributeValue*/, float /*NewAttributeValue*/ );


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
	
	TMap<FGameplayTag, FLingLongAttribute*> CachedAttributes;
	
	UPROPERTY()
	TArray<TObjectPtr<ULingLongAction>> Actions;

	UPROPERTY(EditAnywhere, Category="Actions")
	TArray<TSubclassOf<ULingLongAction>> DefaultActions;

public:
	UActionSystemLingLong();

	FGameplayTagContainer ActiveGameplayTags;
	
	void ApplyAttributeChange(FGameplayTag AttributeTag, float Delta, EAttributeModifiedType ModifyType);
	void StartAction(FGameplayTag InActionName);
	void StopAction(FGameplayTag InActionName);
	void GrantAction(TSubclassOf<ULingLongAction> NewActionClass);
	virtual void InitializeComponent() override;
	FLingLongAttribute* GetAttribute(FGameplayTag InAttributeTag) const;
	FOnAttributeChanged& GetAttributeListener(FGameplayTag AttributeTag);
};
