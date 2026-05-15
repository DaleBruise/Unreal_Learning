// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "LingLongBTDecorator_IsLowHealth.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECTS56_API ULingLongBTDecorator_IsLowHealth : public UBTDecorator
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditAnywhere, Category = "AI", meta = (ClampMin = 0.0f, ClampMax = 1.0f))
	float LowHealthFraction = 0.3f;
	
public:
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	
};
