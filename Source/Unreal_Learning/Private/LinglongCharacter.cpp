// Fill out your copyright notice in the Description page of Project Settings.

#include "LinglongCharacter.h"
#include "DrawDebugHelpers.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Camera/CameraComponent.h"

#include "SInteractionComponent.h"
#include "SattributeComponent.h"

// Sets default values
ALinglongCharacter::ALinglongCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	this->_spring_arm_comp = CreateDefaultSubobject<USpringArmComponent>("spring_arm_comp");
	this->_spring_arm_comp->SetupAttachment(RootComponent);
	this->_spring_arm_comp->bUsePawnControlRotation = true;

	this->_camera_comp = CreateDefaultSubobject<UCameraComponent>("camera_comp");
	this->_camera_comp->SetupAttachment(this->_spring_arm_comp);

	this->_interaction_comp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");

	this->_attr_comp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	this->bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ALinglongCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALinglongCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

#ifdef _debug 
	/*Rotation Visualization*/
	const float DrawScale = 100.0f;
	const float Thickness = 5.0f;

	auto LineStart = GetActorLocation();
	LineStart += GetActorRightVector() * 100.0f;

	FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector() * 100.0f);
	DrawDebugDirectionalArrow(GetWorld(),
		LineStart,
		ActorDirection_LineEnd,
		DrawScale,
		FColor::Yellow,
		false,
		.0f,
		0,
		Thickness);

	FVector ControllerDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.0f);
	DrawDebugDirectionalArrow(GetWorld(),
		LineStart,
		ControllerDirection_LineEnd,
		DrawScale,
		FColor::Green,
		false,
		.0f,
		0,
		Thickness);
	
#endif
}

// Called to bind functionality to input
void ALinglongCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ALinglongCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALinglongCharacter::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ALinglongCharacter::Jump);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ALinglongCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ALinglongCharacter::PrimaryInteract);

}

void ALinglongCharacter::MoveForward(float value) {
	auto ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.f;
	ControlRot.Roll = 0.f;

	/*
	* Pitch（俯仰角）：rotate around the Y axis
	* Yaw（偏航角）：rotate around the Z axis
	* Roll（翻滚角）：rotate around the X axis
	*/

	AddMovementInput(ControlRot.Vector(), value);
}

void ALinglongCharacter::MoveRight(float value) {
	auto ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.f;
	ControlRot.Roll = 0.f;

	/* X = Forward(Red)
	* Y = Right(Green)
	* Z = Up(Blue)
	*/
	auto RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, value);
}

void ALinglongCharacter::Jump() {
	ACharacter::Jump();
}

void ALinglongCharacter::PrimaryAttack() {
	PlayAnimMontage(this->_attack_anim);

	GetWorldTimerManager().SetTimer(
		TimerHandle_PrimaryAttack, this, 
		&ALinglongCharacter::PrimaryAttack_TimerElapsed, 
		0.2f);
}

void ALinglongCharacter::PrimaryInteract()
{
	if (this->_interaction_comp != nullptr)
		this->_interaction_comp->PrimaryInteract();
}

void ALinglongCharacter::PrimaryAttack_TimerElapsed()
{
	if (ensure(ProjectileClass != nullptr))
	{
		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
		auto SpawnTM = FTransform(GetActorRotation(), HandLocation);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		GetWorld()->SpawnActor<AActor>(this->ProjectileClass, SpawnTM, SpawnParams);
	}
}