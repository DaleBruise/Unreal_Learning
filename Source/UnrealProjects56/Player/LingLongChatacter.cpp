// Fill out your copyright notice in the Description page of Project Settings.

#include "LingLongChatacter.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "SharedGameplayTags.h"

#include "ActionSystem/ActionSystemLingLong.h"

#include "GameFramework/SpringArmComponent.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"


ALingLongCharacter::ALingLongCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->SpringArmComp = this->CreateDefaultSubobject<USpringArmComponent>(
		TEXT("SpringArmComp"));
	this->SpringArmComp->bUsePawnControlRotation = true;
	this->SpringArmComp->SetupAttachment(RootComponent);

	this->CameraComp = this->CreateDefaultSubobject<UCameraComponent>(
		TEXT("CameraComp"));
	this->CameraComp->SetupAttachment(this->SpringArmComp);

	this->ActionSystemComp = this->CreateDefaultSubobject<UActionSystemLingLong>(
		TEXT("ActionSystemComp"));
	this->ActionSystemComp->SetDefaultAttributeSet(ThisClass::StaticClass());

	this->AttackAnimDelay = 0.2f;
}

void ALingLongCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	/* Movements */
	EnhancedInput->BindAction(this->Input_Move,
	                          ETriggerEvent::Triggered,
	                          this,
	                          &ALingLongCharacter::Move);

	EnhancedInput->BindAction(this->Input_Look,
	                          ETriggerEvent::Triggered,
	                          this,
	                          &ALingLongCharacter::Look);

	EnhancedInput->BindAction(this->Input_Jump,
	                          ETriggerEvent::Triggered,
	                          this,
	                          &ALingLongCharacter::Jump);

	EnhancedInput->BindAction(this->Input_Sprint,
	                          ETriggerEvent::Started,
	                          this,
	                          &ThisClass::StartAction,
	                          SharedGameplayTags::Action_Sprint.GetTag()); //TODO

	EnhancedInput->BindAction(this->Input_Sprint,
	                          ETriggerEvent::Completed,
	                          this,
	                          &ThisClass::StopAction,
	                          SharedGameplayTags::Action_Sprint.GetTag()); //TODO

	/* Projectiles */
	EnhancedInput->BindAction(this->Input_PrimaryAttack,
	                          ETriggerEvent::Triggered,
	                          this,
	                          &ThisClass::StartAction,
	                          SharedGameplayTags::Action_PrimaryAttack.GetTag());
	EnhancedInput->BindAction(this->Input_SecondaryAttack,
	                          ETriggerEvent::Triggered,
	                          this,
	                          &ThisClass::StartAction,
	                          SharedGameplayTags::Action_SecondaryAttack.GetTag());
	EnhancedInput->BindAction(this->Input_SpecialAttack,
	                          ETriggerEvent::Triggered,
	                          this,
	                          &ThisClass::StartAction,
	                          SharedGameplayTags::Action_SpecialAttack.GetTag());
}

void ALingLongCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	this->GetMesh()->SetOverlayMaterialMaxDrawDistance(1);

	this->ActionSystemComp->GetAttributeListener(SharedGameplayTags::Attribute_Health)
	    .AddUObject(this, &ThisClass::OnHealthChanged);
}

void ALingLongCharacter::Move(const FInputActionValue& InValue)
{
	/*
	* Pitch（俯仰角）：rotate around the Y axis
	* Yaw（偏航角）：rotate around the Z axis
	* Roll（翻滚角）：rotate around the X axis
	*/

	FVector2D InputValue = InValue.Get<FVector2D>();

	/* Forward / Backward*/
	auto ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.f;
	AddMovementInput(ControlRot.Vector(), InputValue.X);

	/* Right / Left */
	FVector RightDirection = ControlRot.RotateVector(FVector::RightVector);
	AddMovementInput(RightDirection, InputValue.Y);
}

void ALingLongCharacter::Look(const FInputActionInstance& InValue)
{
	FVector2D InputValue = InValue.GetValue().Get<FVector2D>();
	this->AddControllerPitchInput(InputValue.Y);
	this->AddControllerYawInput(InputValue.X);
	/* In Mouse input, Yaw corresponds to the axis X because of the 2D dimension that mouse only has*/
}

void ALingLongCharacter::OnHealthChanged(FGameplayTag AttributeTag, float NewHealth, float OldHealth)
{
	// float DamageAmount = NewHealth - OldHealth;

	/* Died ? */
	if (FMath::IsNearlyZero(NewHealth) && OldHealth > 0.0f)
	{
		this->DisableInput(nullptr);

		this->GetMovementComponent()->StopMovementImmediately();

		this->PlayAnimMontage(this->PlayerDeathMontage);
	}
}

float ALingLongCharacter::TakeDamage(float DamageAmount,
                                     struct FDamageEvent const& DamageEvent,
                                     class AController* EventInstigator,
                                     AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser) * (-1.0f);

	this->ActionSystemComp->ApplyAttributeChange(
		SharedGameplayTags::Attribute_Health,
		ActualDamage,
		EAttributeModifiedType::Base);

	const float RageToAdd = DamageAmount * 0.75;
	this->ActionSystemComp->ApplyAttributeChange(SharedGameplayTags::Attribute_Rage,
	                                             RageToAdd,
	                                             EAttributeModifiedType::Modifier);

	this->GetMesh()->SetOverlayMaterialMaxDrawDistance(0);

	// this->GetMesh()->SetScalarParameterValueOnMaterials(
	// 	"TimeToHit",
	// 	this->GetWorld()->TimeSeconds);

	this->GetMesh()->SetCustomPrimitiveDataFloat(
		0,
		this->GetWorld()->TimeSeconds);

	this->GetWorldTimerManager().SetTimer(this->OverlayTimerHandle,
	                                      [this]()
	                                      {
		                                      this->GetMesh()->SetOverlayMaterialMaxDrawDistance(1);
	                                      },
	                                      1.0f,
	                                      false);

	return ActualDamage;
}

void ALingLongCharacter::StartAction(FGameplayTag InActionName)
{
	this->ActionSystemComp->StartAction(InActionName);
}

void ALingLongCharacter::StopAction(FGameplayTag InActionName)
{
	this->ActionSystemComp->StopAction(InActionName);
}

void ALingLongCharacter::Jump()
{
	Super::Jump();
}
