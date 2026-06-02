// Fill out your copyright notice in the Description page of Project Settings.


#include "LingLongBTDecorator_IsLowHealth.h"
#include "AIController.h"
#include "SharedGameplayTags.h"

#include "ActionSystem/ActionSystemLingLong.h"


bool ULingLongBTDecorator_IsLowHealth::CalculateRawConditionValue(
	UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	// BT should have been stopped already with no pawn
	check(Pawn);

	UActionSystemLingLong* ActionComp = Pawn->GetComponentByClass<UActionSystemLingLong>();
	if (ensure(ActionComp))
	{
		// check(false);
		// Is low health?

		const float ActionHealth = ActionComp->GetAttributeValue(
			SharedGameplayTags::Attribute_Health);
		const float ActionHealthMax = ActionComp->GetAttributeValue(
			SharedGameplayTags::Attribute_MaxHealth);
		const float HealthFraction = ActionHealth / ActionHealthMax;

		return HealthFraction < this->LowHealthFraction;
	}

	return false;
}
