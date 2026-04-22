// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemChest.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASItemChest::ASItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	this->_base_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = this->_base_mesh;

	this->_lid_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	this->_lid_mesh->SetupAttachment(this->_base_mesh);

	this->_target_pitch = 110.0f;
}

void ASItemChest::Interact_Implementation(APawn* InstigatorPawn) 
{
	this->_lid_mesh->SetRelativeRotation(FRotator(this->_target_pitch, 0, 0));
}

// Called when the game starts or when spawned
void ASItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

