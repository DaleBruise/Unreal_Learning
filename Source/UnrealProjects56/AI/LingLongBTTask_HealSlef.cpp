// Fill out your copyright notice in the Description page of Project Settings.


#include "LingLongBTTask_HealSlef.h"
#include "AIController.h"
#include "SharedGameplayTags.h"

#include "ActionSystem/ActionSystemLingLong.h"

EBTNodeResult::Type ULingLongBTTask_HealSlef::ExecuteTask(
	UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory)
{
	auto Pawn = OwnerComp.GetAIOwner()->GetPawn();
	check(Pawn);
	
	auto ActionComp = Pawn->GetComponentByClass<UActionSystemLingLong>();
	if (ActionComp != nullptr)
	{
		ActionComp->ApplyAttributeChange(
			SharedGameplayTags::Attribute_Health,
			this->HealAmount,
			EAttributeModifiedType::Base);
		
		
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}
