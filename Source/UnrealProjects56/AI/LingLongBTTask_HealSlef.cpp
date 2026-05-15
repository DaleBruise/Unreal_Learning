// Fill out your copyright notice in the Description page of Project Settings.


#include "LingLongBTTask_HealSlef.h"
#include "AIController.h"

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
		ActionComp->ApplyHealthChange(this->HealAmount);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}
