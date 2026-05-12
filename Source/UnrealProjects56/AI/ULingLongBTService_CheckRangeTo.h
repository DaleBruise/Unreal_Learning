// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ULingLongBTService_CheckRangeTo.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECTS56_API UULingLongBTService_CheckRangeTo : public UBTService
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector TargetActorKey;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector WithinRangeKey;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	float MaxAttackRange = 500.0f;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp,
	                      uint8* NodeMemory,
	                      float DeltaSeconds) override;
};
