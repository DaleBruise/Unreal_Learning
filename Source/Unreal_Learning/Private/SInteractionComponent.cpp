// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"
#include "SGamePlayInterface.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USInteractionComponent::PrimaryInteract()
{
	/*Check if there is something that collides between the line segment*/
	AActor* MyOwner = GetOwner();
	FVector EyeLocation; //This may not the correct position in 3rd Game
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	auto End = EyeLocation + (EyeRotation.Vector() * 1000);

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);

	/*FHitResult Hit;
	bool IfLineHit = GetWorld()->LineTraceSingleByObjectType(
		Hit,
		EyeLocation, End,
		ObjectQueryParams
	);*/

	constexpr float Radius = 30.0f;
	FCollisionShape Shape;
	Shape.SetSphere(Radius);

	TArray<FHitResult> Hits;
	bool IfSphereHit = GetWorld()->SweepMultiByObjectType(
		Hits,
		EyeLocation, End,
		FQuat::Identity,
		ObjectQueryParams,
		Shape
	);
	FColor LineColor = IfSphereHit ? FColor::Green : FColor::Red;

	for (const auto& Hit : Hits) {
		AActor* HitActor = Hit.GetActor();
		if (HitActor != nullptr) {
			if (HitActor->Implements<USGamePlayInterface>()) {
				APawn* MyPawn = Cast<APawn>(MyOwner);
				ISGamePlayInterface::Execute_Interact(HitActor, MyPawn);
				break;
			}
		}

		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, LineColor, false, 20.f);
	}

	/*Draw debug*/
	DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.0f, 0, 2.0f);
}

