// Fill out your copyright notice in the Description page of Project Settings.


#include "LingLongPlayerController.h"
#include "EnhancedInputComponent.h"
#include "InteractionComponent.h"


ALingLongPlayerController::ALingLongPlayerController()
{
	this->InteractionComp = CreateDefaultSubobject<UInteractionComponent>(
		TEXT("InteractionComp"));
}

void ALingLongPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);

	EnhancedInput->BindAction(this->Input_Interact,
	                          ETriggerEvent::Triggered,
	                          this,
	                          &ALingLongPlayerController::StartInteract);
}
 
void ALingLongPlayerController::StartInteract()
{
	this->InteractionComp->Interact();
}
