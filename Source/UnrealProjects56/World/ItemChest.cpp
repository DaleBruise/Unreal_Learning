// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemChest.h"
#include "NiagaraFunctionLibrary.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
AItemChest::AItemChest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	this->BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(
		TEXT("BaseMeshComp"));
	this->BaseMeshComp->SetCollisionProfileName("Interaction");
	this->RootComponent = this->BaseMeshComp;

	this->LidMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(
		TEXT("LidMeshComp"));
	this->LidMeshComp->SetCollisionProfileName("Interaction");
	this->LidMeshComp->SetupAttachment(this->BaseMeshComp);
}

void AItemChest::ChestAnimationComplete() const
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,
	                                               this->TreasureBurstEffect,
	                                               this->GetActorLocation());

	UGameplayStatics::PlaySoundAtLocation(this,
	                                      this->TreasureBurstSound,
	                                      this->GetActorLocation(),
	                                      FRotator::ZeroRotator);
}

// Called every frame
void AItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->AnimCurrentPitch = FMath::FInterpConstantTo(
		this->AnimCurrentPitch,
		this->AnimTargetPitch,
		DeltaTime,
		this->AnimSpeed);

	this->LidMeshComp->SetRelativeRotation(
		FRotator(this->AnimCurrentPitch, .0f, .0f));

	if (FMath::IsNearlyEqual(this->AnimCurrentPitch,
	                         this->AnimTargetPitch))
	{
		/*Animation Ends*/
		this->SetActorTickEnabled(false);

		this->ChestAnimationComplete();
	}
}

void AItemChest::Interact_Implementation()
{
	/*Animation Starts*/
	this->SetActorTickEnabled(true);
}
