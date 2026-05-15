// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSystemLingLong.h"

#include "Player/LingLongChatacter.h"


// Sets default values for this component's properties
UActionSystemLingLong::UActionSystemLingLong()
{
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
