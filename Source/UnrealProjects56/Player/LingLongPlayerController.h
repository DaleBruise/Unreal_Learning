// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LingLongPlayerController.generated.h"

class UInputAction;
class UInteractionComponent;

UCLASS()
class UNREALPROJECTS56_API ALingLongPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UInteractionComponent> InteractionComp;;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Interact;;
	
	virtual void SetupInputComponent() override;
	
	void StartInteract();
	
public:
	
	ALingLongPlayerController();
	
};
