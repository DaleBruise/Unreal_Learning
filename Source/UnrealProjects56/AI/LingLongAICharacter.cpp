// Fill out your copyright notice in the Description page of Project Settings.


#include "LingLongAICharacter.h"
#include "SharedGameplayTags.h"

#include "ActionSystem/ActionSystemLingLong.h"
#include "ActionSystem/LingLongAttributeSet.h"

// Sets default values
ALingLongAICharacter::ALingLongAICharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->ActionSystemComp = this->CreateDefaultSubobject<UActionSystemLingLong>(TEXT(
		"ActionSystemComp"));
	this->ActionSystemComp->SetDefaultAttributeSet(ULingLongMonsterAttributeSet::StaticClass());
}

float ALingLongAICharacter::TakeDamage(float DamageAmount,
                                       struct FDamageEvent const& DamageEvent,
                                       class AController* EventInstigator,
                                       AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser) * (-1.0f);

	this->ActionSystemComp->ApplyAttributeChange(
		SharedGameplayTags::Attribute_Health,
		ActualDamage,
		EAttributeModifiedType::Base);

	return ActualDamage;
}
