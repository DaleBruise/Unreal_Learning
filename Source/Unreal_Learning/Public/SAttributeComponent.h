// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREAL_LEARNING_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USAttributeComponent();

protected:
	/*
	 * EditAnywhere - edit in BP editor and per-instance in level.
	 * VisibleAnywhere - 'read-only' in editor and level.
	 * EditDefaultsOnly - hide variable per-instance, edit in BP editor only.
	 * BlueprintReadOnly - read-only in the Blueprint scripting. 
	 * BlueprintReadWrite - read-write access in Blueprints.
	 * Category = "" - display only for detail panels and blueprint context menu.
	 */

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float _health;

public:
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(float Delta);
};
