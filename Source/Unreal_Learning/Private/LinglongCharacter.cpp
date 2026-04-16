// Fill out your copyright notice in the Description page of Project Settings.


#include "LinglongCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ALinglongCharacter::ALinglongCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	this->_spring_arm_comp = CreateDefaultSubobject<USpringArmComponent>("spring_arm_comp");
	this->_camera_comp = CreateDefaultSubobject<UCameraComponent>("camera_comp");

	this->_spring_arm_comp->SetupAttachment(RootComponent);
	this->_camera_comp->SetupAttachment(this->_spring_arm_comp);

}

// Called when the game starts or when spawned
void ALinglongCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALinglongCharacter::_MoveForward(float value) {
	AddMovementInput(GetActorForwardVector(), value);
}

// Called every frame
void ALinglongCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALinglongCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ALinglongCharacter::_MoveForward);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
}
