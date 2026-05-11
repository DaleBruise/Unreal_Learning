// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractionComponent.h"
#include "LingLongTypes.h"

#include "Engine/OverlapResult.h"

#include "Core/InteractionInterface.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInteractionComponent::Interact()
{
	auto* InteractInterface = Cast<IInteractionInterface>(this->SelectedActor);
	if (InteractInterface != nullptr)
	{
		InteractInterface->Interact();
	}
}

// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime,
                                          ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if (IfShowDebug && this->SelectedActor != nullptr)
	// {
	// 	UE_LOG(LogTemp, 
	// 		Log, 
	// 		TEXT("The Selected Actor is: %s"), *this->SelectedActor->GetName());
	// }
	
	APlayerController* PC = CastChecked<APlayerController>(GetOwner());
	if (PC != nullptr)
	{
		FVector Center = PC->GetPawn()->GetActorLocation();

		FCollisionShape Shape;
		Shape.SetSphere(this->InteractionRadius);

		ECollisionChannel CollisionChannel = COLLISION_INTERACTION;
		TArray<FOverlapResult> Overlaps;
		this->GetWorld()->OverlapMultiByChannel(Overlaps,
		                                        Center,
		                                        FQuat::Identity,
		                                        CollisionChannel,
		                                        Shape);

		AActor* BestActor = nullptr;
		float HighestDotResult = -1.0f;

		for (const auto& Lap : Overlaps)
		{
			FVector OverlapLocation = Lap.GetActor()->GetActorLocation();
			FVector OverlapDirection = (OverlapLocation - Center).GetSafeNormal();

			float DotResult = FVector::DotProduct(OverlapDirection,
			                                      PC->GetControlRotation().Vector());

			if (DotResult > HighestDotResult)
			{
				BestActor = Lap.GetActor();
				HighestDotResult = DotResult;
			}

			if (IfShowDebug)
			{
				DrawDebugBox(this->GetWorld(),
				             OverlapLocation,
				             FVector(50.0f),
				             FColor::Green);

				FString DebugString = FString::Printf(TEXT("Dot : %f"), DotResult);
				DrawDebugString(this->GetWorld(),
				                OverlapLocation,
				                DebugString,
				                nullptr,
				                FColor::White,
				                .0f,
				                true);
			}
		}

		this->SelectedActor = BestActor;

		if (BestActor != nullptr && IfShowDebug)
		{
			DrawDebugBox(this->GetWorld(),
			             BestActor->GetActorLocation(),
			             FVector(60.0f),
			             FColor::Blue);
		}

		if (IfShowDebug)
		{
			DrawDebugSphere(this->GetWorld(),
			                Center,
			                this->InteractionRadius,
			                32,
			                FColor::White);
		}
	}
}
