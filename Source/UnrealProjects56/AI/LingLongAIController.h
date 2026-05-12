// Fill out your copyright notice in the Description page of Project Settings.
// The Behavior Tree will run in here

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "LingLongAIController.generated.h"

class UBehaviorTree;

UCLASS()
class UNREALPROJECTS56_API ALingLongAIController : public AAIController
{
	GENERATED_BODY()

public:

	ALingLongAIController();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	virtual void BeginPlay() override;

};
