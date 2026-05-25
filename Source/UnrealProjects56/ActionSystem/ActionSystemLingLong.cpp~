// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystemLingLong.h"

#include "LingLongAction.h"
#include "LingLongAttributeSet.h"


// Sets default values for this component's properties
UActionSystemLingLong::UActionSystemLingLong()
{
	this->bWantsInitializeComponent = true;
}

void UActionSystemLingLong::InitializeComponent()
{
	Super::InitializeComponent();

	if (this->Attributes == nullptr)
	{
		this->Attributes = NewObject<ULingLongAttributeSet>(this, ULingLongAttributeSet::StaticClass());
		UE_LOG(LogTemp, Log, TEXT("No default AttributeSet defined for %s."),
		       *GetNameSafe(this->GetOwner()))
	}


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

void UActionSystemLingLong::BeginPlay()
{
	Super::BeginPlay();

	this->Attributes->InitializeAttributes();
}

void UActionSystemLingLong::ApplyAttributeChange(FGameplayTag AttributeTag,
                                                 float Delta,
                                                 EAttributeModifiedType ModifyType)
{
	auto FoundAttribute = this->GetAttribute(AttributeTag);
	check(FoundAttribute);

	float OldValue = FoundAttribute->GetValue();
	switch (ModifyType)
	{
	case Base:
		FoundAttribute->Base += Delta;
		break;
	case Modifier:
		FoundAttribute->Modifier += Delta;
		break;
	case OverrideBase:
		FoundAttribute->Base += Delta;
		break;
	default:
		check(false);
	}

	/* non-dynamic, native C++ listeners*/
	this->Attributes->PostAttributeChanged();
	auto* NativeEvent = this->AttributeListeners.Find(AttributeTag);
	if (NativeEvent != nullptr)
	{
		NativeEvent->Broadcast(AttributeTag, FoundAttribute->GetValue(), OldValue);
	}

	/* dynamic, blueprint listeners*/
	auto DynamicEvents = this->AttributeDynamicListeners.Find(AttributeTag);
	if (DynamicEvents != nullptr)
	{
		for (auto& SubEvent : *DynamicEvents)
		{
			bool IfBound = SubEvent.ExecuteIfBound(AttributeTag, FoundAttribute->GetValue(), OldValue);
			if (!IfBound)
			{
				DynamicEvents->Remove(SubEvent);
				UE_LOG(LogTemp, Log, TEXT("Cleaned up expired attribute delegate for %s"),
				       *GetNameSafe(GetOwner()));
			}
		}
	}

	UE_LOGFMT(LogTemp, Log, "Attribute: {0}, New: {1}, Old: {2}",
	          AttributeTag.ToString(),
	          FoundAttribute->GetValue(),
	          OldValue);
}

void UActionSystemLingLong::AddDynamicAttributeChange(FOnAttributeDynamicChanged Event,
                                                      FGameplayTag AttributeTag)
{
	TArray<FOnAttributeDynamicChanged>& Events = this->AttributeDynamicListeners.FindOrAdd(AttributeTag);
	Events.Add(Event);
}

void UActionSystemLingLong::RemoveDynamicAttributeListener(FOnAttributeDynamicChanged Event)
{
	for (auto& Listener : this->AttributeDynamicListeners)
	{
		if (Listener.Value.RemoveSingle(Event) > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Successfully removed blueprint binding"))
			break;
		}
	}
}

float UActionSystemLingLong::GetAttributeValue(FGameplayTag InAttributeTag) const
{
	auto FoundAttribute = this->GetAttribute(InAttributeTag);
	if (FoundAttribute != nullptr)
	{
		return FoundAttribute->GetValue();
	}

	return -1;
}

void UActionSystemLingLong::SetDefaultAttributeSet(TSubclassOf<ULingLongAttributeSet> AttributeSetClass)
{
	check(!this->HasBeenInitialized());
	
	FObjectInitializer& ObjectInitializer = FObjectInitializer::Get();
	this->Attributes = Cast<ULingLongAttributeSet>(
		ObjectInitializer.CreateDefaultSubobject(this,
		                                         TEXT("Attributes"),
		                                         AttributeSetClass,
		                                         AttributeSetClass));
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
		if (Action->GetActionName() == InActionName
			&& Action->IsRunning())
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

FOnAttributeChanged& UActionSystemLingLong::GetAttributeListener(FGameplayTag AttributeTag)
{
	return this->AttributeListeners.FindOrAdd(AttributeTag);
}
