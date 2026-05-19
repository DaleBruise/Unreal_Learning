// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LingLongAction.h"
#include "LingLongAction_Projectile.generated.h"

class AProjectileBase;

class UAnimMontage;
class UNiagaraSystem;
class USoundBase;
class UActionSystemLingLong;

/**
 * 
 */
UCLASS(Abstract)
class UNREALPROJECTS56_API ULingLongAction_Projectile : public ULingLongAction
{
	GENERATED_BODY()

public:
	virtual void StartAction_Implementation() override;
	
	ULingLongAction_Projectile();
	void AttackTimerElapsed();
	
protected:
	UPROPERTY(EditAnywhere, Category = "ProjectileAttack")
	TSubclassOf<AProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "ProjectileAttack")
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "ProjectileAttack")
	TObjectPtr<UNiagaraSystem> CastingEffect;

	UPROPERTY(EditDefaultsOnly, Category = "ProjectileAttack")
	TObjectPtr<USoundBase> CastingSound;


	UPROPERTY(VisibleAnywhere, Category = "ProjectileAttack")
	FName MuzzleSocketName;
	
};
