// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystemLingLong.h"

#include "LingLongAction.h"


// Sets default values for this component's properties
UActionSystemLingLong::UActionSystemLingLong()
{
	this->bWantsInitializeComponent = true;
}

void UActionSystemLingLong::ApplyHealthChange(float Value)
{
	const float OldHealth = this->Attribute.Health;

	this->Attribute.Health = FMath::Clamp(this->Attribute.Health + Value,
	                                      0.0f,
	                                      this->Attribute.HealthMax);

	if (!FMath::IsNearlyEqual(OldHealth, this->Attribute.Health))
	{
		this->OnHealthChanged.Broadcast(this->Attribute.Health, OldHealth);
	}

	UE_LOG(LogTemp, Log, TEXT("Current Health is : %f"), this->Attribute.Health);
}

void UActionSystemLingLong::StartAction(FName InActionName)
{
	for (auto const& Action : this->Actions)
	{
		if (Action->GetActionName() == InActionName)
		{
			Action->StartAction();
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

void UActionSystemLingLong::InitializeComponent()
{
	Super::InitializeComponent();

	for (auto const& Action : this->DefaultActions)
	{
		if (ensure(Action))
		{
			this->GrantAction(Action);
		}
	}
}

float UActionSystemLingLong::GetHealth() const
{
	return this->Attribute.Health;
}

float UActionSystemLingLong::GetHealthMax() const
{
	return this->Attribute.HealthMax;
}

bool UActionSystemLingLong::IsFullHealth() const
{
	return FMath::IsNearlyEqual(this->Attribute.Health,
	                            this->Attribute.HealthMax);
}
