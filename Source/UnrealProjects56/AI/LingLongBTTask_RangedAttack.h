// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "LingLongBTTask_RangedAttack.generated.h"

class AProjectileBase;

UCLASS()
class UNREALPROJECTS56_API ULingLongBTTask_RangedAttack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere, Category = "AI")
	FName MuzzleSocketName;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector TargetActorKey;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	float MaxBulletSpread = 5.0f;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	TSubclassOf<AProjectileBase> ProjectileClass;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp,
	                                        uint8* NodeMemory) override;
	
	ULingLongBTTask_RangedAttack();
	
};
