// Fill out your copyright notice in the Description page of Project Settings.


#include "LingLongAttributeSet.h"
#include "ActionSystemLingLong.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

/* struct FLingLongAttribute */
float FLingLongAttribute::GetValue() const
{
	return this->Base + this->Modifier;
}

UActionSystemLingLong* ULingLongAttributeSet::GetOwningComponent() const
{
	return Cast<UActionSystemLingLong>(this->GetOuter());
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

/* class ULingLongPawnAttributeSet */
ULingLongPawnAttributeSet::ULingLongPawnAttributeSet()
{
	this->MoveSpeed = FLingLongAttribute(550);
}

void ULingLongPawnAttributeSet::PostAttributeChanged()
{
	Super::PostAttributeChanged();
	
	this->ApplyMoveSpeed();
}

void ULingLongPawnAttributeSet::InitializeAttributes()
{
	Super::InitializeAttributes();
	
	this->ApplyMoveSpeed();
}

void ULingLongPawnAttributeSet::ApplyMoveSpeed()
{
	auto OwningCharacter = Cast<ACharacter>(ULingLongAttributeSet::GetOwningComponent()->GetOwner());
	OwningCharacter->GetCharacterMovement()->MaxWalkSpeed = this->MoveSpeed.GetValue();
}

/* class ULingLongMonsterAttributeSet */
ULingLongMonsterAttributeSet::ULingLongMonsterAttributeSet()
{
	this->MoveSpeed = FLingLongAttribute(450);
}
