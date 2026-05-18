// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LingLongChatacter.generated.h"

struct FInputActionValue;
struct FInputActionInstance;

class USpringArmComponent;
class UCameraComponent;
class UActionSystemLingLong;
class UInputAction;
class ALingLongProjectileMagic;
class UAnimMontage;
class UNiagaraSystem;
class USoundBase;
class AProjectileBase;
// class USInteractionComponent;
// class USAttributeComponent;

UCLASS()
class UNREALPROJECTS56_API ALingLongCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ALingLongCharacter();

protected:
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UActionSystemLingLong> ActionSystemComp;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Move;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Look;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_PrimaryAttack;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_SecondaryAttack;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_SpecialAttack;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Jump;

	UPROPERTY(EditDefaultsOnly, Category = "PrimaryAttack")
	TSubclassOf<AProjectileBase> PrimaryAttackProjectile;

	UPROPERTY(EditDefaultsOnly, Category="PrimaryAttack")
	TSubclassOf<AProjectileBase> SecondaryAttackProjectile;

	UPROPERTY(EditDefaultsOnly, Category="PrimaryAttack")
	TSubclassOf<AProjectileBase> SpecialAttackProjectile;

	UPROPERTY(EditAnywhere, Category = "PrimaryAttack")
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "PrimaryAttack")
	TObjectPtr<UNiagaraSystem> CastingEffect;

	UPROPERTY(EditDefaultsOnly, Category = "PrimaryAttack")
	TObjectPtr<USoundBase> CastingSound;

	UPROPERTY(EditAnywhere, Category = "Death")
	TObjectPtr<UAnimMontage> PlayerDeathMontage;
	

	UPROPERTY(VisibleAnywhere, Category = "PrimaryAttack")
	FName MuzzleSocketName;

	UPROPERTY(VisibleAnywhere, Category = "PrimaryAttack")
	float AttackAnimDelay;


	void Move(const FInputActionValue& InValue);
	void Look(const FInputActionInstance& InValue);
	void Jump();
	void StartProjectileAttack(TSubclassOf<AProjectileBase> ProjectileClass); /* Only cares about if it was triggerred or not */
	void AttackTimerElapsed(TSubclassOf<AProjectileBase> ProjectileClass); /* Only serves StartProjectileAttack() */
	
	UFUNCTION()
	void OnHealthChanged(float NewHealth, float OldHealth);
	
	virtual float TakeDamage(float DamageAmount,
	                         struct FDamageEvent const& DamageEvent,
	                         class AController* EventInstigator,
	                         AActor* DamageCauser) override;
	
	void StartAction(FName InActionName);

public:
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	
};
