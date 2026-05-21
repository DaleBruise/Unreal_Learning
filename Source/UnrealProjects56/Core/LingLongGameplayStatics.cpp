// Fill out your copyright notice in the Description page of Project Settings.


#include "LingLongGameplayStatics.h"

#include "SharedGameplayTags.h"

#include "ActionSystem/LingLongAttributeSet.h"
#include "ActionSystem/ActionSystemLingLong.h"

bool ULingLongGameplayStatics::IsFullHealth(UActionSystemLingLong* ActionComp)
{
	FLingLongAttribute* Health = ActionComp->GetAttribute(SharedGameplayTags::Attribute_Health);
	FLingLongAttribute* MaxHealth = ActionComp->GetAttribute(SharedGameplayTags::Attribute_MaxHealth);

	return FMath::IsNearlyEqual(Health->GetValue(), MaxHealth->GetValue());
}
