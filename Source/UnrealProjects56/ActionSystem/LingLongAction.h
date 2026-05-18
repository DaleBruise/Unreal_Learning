// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "LingLongAction.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECTS56_API ULingLongAction : public UObject
{
	GENERATED_BODY()
	
public:
	
	void StartAction();
	FName GetActionName() const;
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category="Actions")
	FName ActionName = FName("PrimaryAttack");
};
