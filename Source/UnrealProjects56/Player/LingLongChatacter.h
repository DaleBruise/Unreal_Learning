// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LingLongChatacter.generated.h"

struct FInputActionValue;
struct FInputActionInstance;
struct FGameplayTag;

class USpringArmComponent;
class UCameraComponent;
class UActionSystemLingLong;
class UInputAction;
class UAnimMontage;
class USoundBase;

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

	/* Movements */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Move;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Look;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Jump;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Sprint;
	
	/* Projectiles */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_PrimaryAttack;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_SecondaryAttack;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_SpecialAttack;
	
	/* Animations */
	UPROPERTY(EditAnywhere, Category = "Death")
	TObjectPtr<UAnimMontage> PlayerDeathMontage;
	
	UPROPERTY(VisibleAnywhere, Category = "PrimaryAttack")
	float AttackAnimDelay;


	void Move(const FInputActionValue& InValue);
	void Look(const FInputActionInstance& InValue);
	void Jump();
	void OnHealthChanged(FGameplayTag AttributeTag, float NewHealth, float OldHealth);
	void StartAction(FGameplayTag InActionName);
	void StopAction(FGameplayTag InActionName);
	
	virtual float TakeDamage(float DamageAmount,
	                         struct FDamageEvent const& DamageEvent,
	                         class AController* EventInstigator,
	                         AActor* DamageCauser) override;

public:
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	
};
