// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "LingLongBTTask_HealSlef.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECTS56_API ULingLongBTTask_HealSlef : public UBTTaskNode
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "AI")
	float HealAmount = 100;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
};
