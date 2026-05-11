// Fill out your copyright notice in the Description page of Project Settings.

#include "LingLongChatacter.h"
#include "EnhancedInputComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "LingLongTypes.h"

#include "ActionSystem/ActionSystemLingLong.h"

#include "Projectiles/LingLongProjectileMagic.h"

#include "GameFramework/SpringArmComponent.h"

#include "Kismet/GameplayStatics.h"

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

	this->MuzzleSocketName = TEXT("Muzzle_01");

	this->AttackAnimDelay = 0.2f;
}

void ALingLongCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

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

	EnhancedInput->BindAction(this->Input_PrimaryAttack,
	                          ETriggerEvent::Triggered,
	                          this,
	                          &ALingLongCharacter::StartProjectileAttack, this->PrimaryAttackProjectile);
	EnhancedInput->BindAction(this->Input_SecondaryAttack,
	                          ETriggerEvent::Triggered,
	                          this,
	                          &ALingLongCharacter::StartProjectileAttack, this->SecondaryAttackProjectile);
	EnhancedInput->BindAction(this->Input_SpecialAttack,
	                          ETriggerEvent::Triggered,
	                          this,
	                          &ALingLongCharacter::StartProjectileAttack, this->SpecialAttackProjectile);
}

void ALingLongCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	this->ActionSystemComp->OnHealthChanged.AddDynamic(this, &ALingLongCharacter::OnHealthChanged);
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

void ALingLongCharacter::StartProjectileAttack(TSubclassOf<AProjectileBase> ProjectileClass)
{
	/* Setting the attack animation and sound */
	this->PlayAnimMontage(this->AttackMontage);

	UNiagaraFunctionLibrary::SpawnSystemAttached(this->CastingEffect,
	                                             this->GetMesh(),
	                                             this->MuzzleSocketName,
	                                             FVector::ZeroVector,
	                                             FRotator::ZeroRotator,
	                                             EAttachLocation::Type::SnapToTarget,
	                                             true);

	UGameplayStatics::PlaySound2D(this,
	                              this->CastingSound);

	// this->GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack,
	//                                       this,
	//                                       &ALingLongCharacter::AttackTimerElapsed,
	//                                       this->AttackAnimDelay);

	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerDelegate Delegate;
	Delegate.BindUObject(this, &ALingLongCharacter::AttackTimerElapsed, ProjectileClass);
	this->GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack,
	                                      Delegate,
	                                      this->AttackAnimDelay,
	                                      false);
}

void ALingLongCharacter::AttackTimerElapsed(TSubclassOf<AProjectileBase> ProjectileClass)
{
	/* Setting the projectile location */
	FVector SpawnLocation = this->GetMesh()->GetSocketLocation(this->MuzzleSocketName);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	/* Optimize the projectile's direction */
	FVector EyeLocation = this->CameraComp->GetComponentLocation();
	FRotator EyeRotation = this->GetControlRotation();
	FVector TraceEnd = EyeLocation + (EyeRotation.Vector() * 5000.0f);

	FHitResult Hit;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	FVector AdjustedTargetLocation;
	if (this->GetWorld()->LineTraceSingleByChannel(Hit,
	                                               EyeLocation,
	                                               TraceEnd,
	                                               ECC_GameTraceChannel2,
	                                               CollisionParams))
	{
		AdjustedTargetLocation = Hit.Location;
	}
	else
	{
		AdjustedTargetLocation = TraceEnd;
	}

	FRotator SpawnRotation = (AdjustedTargetLocation - SpawnLocation).Rotation();

	AActor* NewProjectile = this->GetWorld()->SpawnActor<AActor>(
		ProjectileClass,
		SpawnLocation,
		SpawnRotation,
		SpawnParams);

	this->MoveIgnoreActorAdd(NewProjectile);

	/* Debug stuff */
	if (CVarInteractionDebugDrawing.GetValueOnGameThread())
	{
		float DebugDrawDuration = 5.0f;
		DrawDebugBox(this->GetWorld(),
		             AdjustedTargetLocation,
		             FVector(20.0f),
		             FColor::Green,
		             false,
		             DebugDrawDuration);

		DrawDebugLine(this->GetWorld(),
		              EyeLocation,
		              TraceEnd,
		              FColor::Green,
		              false,
		              DebugDrawDuration);

		DrawDebugLine(this->GetWorld(),
		              SpawnLocation,
		              AdjustedTargetLocation,
		              FColor::Yellow,
		              false,
		              DebugDrawDuration);

		DrawDebugLine(this->GetWorld(),
		              SpawnLocation,
		              SpawnLocation + (this->GetControlRotation().Vector() * 5000.0f),
		              FColor::Purple,
		              false,
		              DebugDrawDuration);
	}
}

void ALingLongCharacter::OnHealthChanged(float NewHealth, float OldHealth)
{
	/* Died ? */
	if (FMath::IsNearlyZero(NewHealth))
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

	this->ActionSystemComp->ApplyHealthChange(ActualDamage);

	return ActualDamage;
}

void ALingLongCharacter::Jump()
{
	Super::Jump();
}
