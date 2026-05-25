// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "LingLongAnimInstance.generated.h"

class UActionSystemLingLong;
UCLASS()
class UNREALPROJECTS56_API ULingLongAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeInitializeAnimation() override;
	
protected:
	
	UPROPERTY(Transient, BlueprintReadOnly, Category=StatusEffects)
	bool bIsSprinting;
	
	UPROPERTY(Transient, BlueprintReadOnly)
	TObjectPtr<UActionSystemLingLong> ActionComp;
};
