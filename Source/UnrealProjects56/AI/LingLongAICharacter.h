// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LingLongAICharacter.generated.h"

class UActionSystemLingLong;

UCLASS()
class UNREALPROJECTS56_API ALingLongAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALingLongAICharacter();


protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UActionSystemLingLong> ActionSystemComp;
	
	virtual float TakeDamage(float DamageAmount,
						 struct FDamageEvent const& DamageEvent,
						 class AController* EventInstigator,
						 AActor* DamageCauser) override;
	
};
