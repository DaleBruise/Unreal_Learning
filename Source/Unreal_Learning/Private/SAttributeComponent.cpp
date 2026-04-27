// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	
	this->_health = 100;
}

bool USAttributeComponent::ApplyHealthChange(float Delta)
{
	this->_health += Delta;
	
	this->OnHealthChanged.Broadcast(nullptr, 
		this, 
		this->_health, 
		Delta);
	
	return true;
}