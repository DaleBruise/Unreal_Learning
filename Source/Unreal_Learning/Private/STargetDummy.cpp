// Fill out your copyright notice in the Description page of Project Settings.


#include "STargetDummy.h"
#include "SAttributeComponent.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
ASTargetDummy::ASTargetDummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	this->_mesh_comp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	this->RootComponent = this->_mesh_comp;
	
	this->_attr_comp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
	this->_attr_comp->OnHealthChanged.AddDynamic(this, &ASTargetDummy::OnHealthChanged);
	
}

void ASTargetDummy::OnHealthChanged(AActor* InstigatorActor, 
	USAttributeComponent* OwningComp, 
	float NewHealth,
	float Delta)
{
	if (Delta < 0.0f)
	{
		this->_mesh_comp->SetScalarParameterValueOnMaterials("TimeToHit", 
			GetWorld()->TimeSeconds);
	}
	
}
