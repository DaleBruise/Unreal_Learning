// Fill out your copyright notice in the Description page of Project Settings.


#include "LingLongAnimInstance.h"
#include "SharedGameplayTags.h"

#include "ActionSystem/ActionSystemLingLong.h"

void ULingLongAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (this->ActionComp != nullptr)
	{
		this->bIsSprinting = this->ActionComp->ActiveGameplayTags.HasTag(
		   SharedGameplayTags::StatusEffects_Sprinting);
	}
}

void ULingLongAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	this->ActionComp = 
		this->GetOwningActor()->FindComponentByClass<UActionSystemLingLong>();
}
