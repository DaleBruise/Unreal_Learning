// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LinglongCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USInteractionComponent;
class UAnimMontage;
class USAttributeComponent;

UCLASS()
class UNREAL_LEARNING_API ALinglongCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALinglongCharacter();

protected:
	// Components
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* _spring_arm_comp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* _camera_comp;

	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* _interaction_comp;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* _attack_anim;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USAttributeComponent* _attr_comp;
	
	FTimerHandle TimerHandle_PrimaryAttack;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void MoveForward(float value);
	void MoveRight(float value);
	void Jump();
	void PrimaryAttack();
	void PrimaryInteract();
	void PrimaryAttack_TimerElapsed();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
