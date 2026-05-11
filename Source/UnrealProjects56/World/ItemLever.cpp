// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemLever.h"


// Sets default values
AItemLever::AItemLever()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	this->BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(
		TEXT("BaseLeverMeshComp"));
	this->RootComponent = this->BaseMeshComp;

	this->LeverMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(
		TEXT("LeverMeshComp"));
	this->LeverMeshComp->SetupAttachment(this->BaseMeshComp);
	this->LeverMeshComp->SetRelativeRotation(FRotator(this->AnimCurrentPitch, .0f, .0f));
}

// Called when the game starts or when spawned
void AItemLever::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AItemLever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->AnimCurrentPitch = FMath::FInterpConstantTo(
		this->AnimCurrentPitch,
		this->AnimTargetPitch,
		DeltaTime,
		this->AnimSpeed);

	this->LeverMeshComp->SetRelativeRotation(
		FRotator(this->AnimCurrentPitch, .0f, .0f));

	if (FMath::IsNearlyEqual(this->AnimCurrentPitch,
	                         this->AnimTargetPitch))
	{
		/*Animation Ends*/
		this->SetActorTickEnabled(false);
	}
}

void AItemLever::Interact()
{
	/*Animation Starts*/
	this->SetActorTickEnabled(true);
}
