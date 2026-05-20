// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystemLingLong.h"

#include "LingLongAction.h"
#include "LingLongAttributeSet.h"


// Sets default values for this component's properties
UActionSystemLingLong::UActionSystemLingLong()
{
	this->bWantsInitializeComponent = true;
	
	this->AttributeSetClass = ULingLongAttributeSet::StaticClass();
}

void UActionSystemLingLong::InitializeComponent()
{
	Super::InitializeComponent();
	
	this->Attributes = NewObject<ULingLongAttributeSet>(this, this->AttributeSetClass);

	for (TFieldIterator<FStructProperty> PropIt(this->Attributes->GetClass()); 
		PropIt != nullptr; ++PropIt)
	{
		FStructProperty* StructProp = *PropIt;
		auto FoundAttribute = 
			StructProp->ContainerPtrToValuePtr<FLingLongAttribute>(this->Attributes);
		
		FName AttributeTagName = FName("Attribute." + PropIt->GetName());
		FGameplayTag AttributeTag = FGameplayTag::RequestGameplayTag(AttributeTagName);
		
		this->CachedAttributes.Add(AttributeTag, FoundAttribute);
	}
	
	for (auto const& Action : this->DefaultActions)
	{
		if (ensure(Action))
		{
			this->GrantAction(Action);
		}
	}
}

void UActionSystemLingLong::ApplyHealthChange(float Value)
{
	// const float OldHealth = this->Attribute.Health;
	//
	// this->Attribute.Health = FMath::Clamp(this->Attribute.Health + Value,
	//                                       0.0f,
	//                                       this->Attribute.HealthMax);
	//
	// if (!FMath::IsNearlyEqual(OldHealth, this->Attribute.Health))
	// {
	// 	this->OnHealthChanged.Broadcast(this->Attribute.Health, OldHealth);
	// }
	//
	// UE_LOG(LogTemp, Log, TEXT("Current Health is : %f"), this->Attribute.Health);
}

void UActionSystemLingLong::StartAction(FGameplayTag InActionName)
{
	for (const auto& Action : this->Actions)
	{
		if (Action->GetActionName() == InActionName)
		{
			if (Action->CanStart())
			{
				Action->StartAction();
			}
			return;
		}
	}

	UE_LOG(LogTemp, Log, TEXT("No Action found with name %s "), *InActionName.ToString());
}

void UActionSystemLingLong::StopAction(FGameplayTag InActionName)
{
	for (const auto& Action : this->Actions)
	{
		if (Action->GetActionName() == InActionName)
		{
			Action->StopAction();
			return;
		}
	}

	UE_LOG(LogTemp, Log, TEXT("No Action found with name %s "), *InActionName.ToString());
}

void UActionSystemLingLong::GrantAction(TSubclassOf<ULingLongAction> NewActionClass)
{
	auto NewAction = NewObject<ULingLongAction>(this,
	                                            NewActionClass);
	this->Actions.Add(NewAction);
}

FLingLongAttribute* UActionSystemLingLong::GetAttribute(FGameplayTag InAttributeTag) const
{
	/* The address of the pointer pointed at couldn't be changed */
	auto FoundAttribute = this->CachedAttributes.Find(InAttributeTag); 
	
	return *FoundAttribute;
}

bool UActionSystemLingLong::IsFullHealth() const
{
	// return FMath::IsNearlyEqual(this->Attribute.Health,
	//                             this->Attribute.HealthMax);
	return true;
}
