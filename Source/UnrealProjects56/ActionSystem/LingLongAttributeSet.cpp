// Fill out your copyright notice in the Description page of Project Settings.


#include "LingLongAttributeSet.h"

/* struct FLingLongAttribute */
float FLingLongAttribute::GetValue() const
{
	return this->Base + this->Modifier;
}

/* class ULingLongHealthAttributeSet */
ULingLongHealthAttributeSet::ULingLongHealthAttributeSet()
{
	this->Health = FLingLongAttribute(100);
	this->MaxHealth = FLingLongAttribute(this->Health.GetValue());
}

void ULingLongHealthAttributeSet::PostAttributeChanged()
{
	this->Health.Base = FMath::Clamp(this->Health.Base,
	                                 0.0f,
	                                 this->MaxHealth.GetValue());
}
