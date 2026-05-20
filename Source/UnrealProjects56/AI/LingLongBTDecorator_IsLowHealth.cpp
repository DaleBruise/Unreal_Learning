// Fill out your copyright notice in the Description page of Project Settings.


#include "LingLongBTDecorator_IsLowHealth.h"
#include "AIController.h"

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
		check(false);
		// Is low health?
		return false;//(ActionComp->GetHealth() / ActionComp->GetHealthMax()) < LowHealthFraction;
	}
	
	return false;
}
