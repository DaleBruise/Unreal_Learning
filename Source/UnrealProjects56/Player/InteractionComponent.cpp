// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractionComponent.h"
#include "LingLongTypes.h"

#include "Engine/OverlapResult.h"

#include "Core/InteractionInterface.h"

// TAutoConsoleVariable<bool> CVarInteractionDebugDrawing(TEXT("game.interaction.DebugDrawing"),
// 	false,
// 	TEXT("Enable interaction debug drawing"),
// 	ECVF_Cheat);

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

	// if (this->SelectedActor != nullptr)
	// {
	// 	IInteractionInterface::Execute_Interact(this->SelectedActor);
	// }
}

// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime,
                                          ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bool bEnableDebugDraw = CVarInteractionDebugDrawing.GetValueOnGameThread();

	APlayerController* PC = CastChecked<APlayerController>(GetOwner());
	if (PC != nullptr)
	{
		FVector Center = PC->GetPawn()->GetActorLocation();
		FVector CameraLocation = PC->PlayerCameraManager->GetCameraLocation();

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
		float HighestWeight = -1.0f;

		for (const auto& Lap : Overlaps)
		{
			FVector Origin;
			FVector BoxExtent;
			Lap.GetActor()->GetActorBounds(true, Origin, BoxExtent);

			// FVector OverlapLocation = Lap.GetActor()->GetActorLocation();
			FVector OverlapDirection = (Origin - CameraLocation).GetSafeNormal();

			float DistanceToSqrd = (Origin - Center).SizeSquared();
			float InteractionRadiusSqrd = this->InteractionRadius * this->InteractionRadius;
			float NormalDistanceResult = 1.0f - (DistanceToSqrd / InteractionRadiusSqrd);

			float DotResult = FVector::DotProduct(OverlapDirection,
			                                      PC->GetControlRotation().Vector());
			float NormalDotResult = DotResult * 0.5f + 0.5f;

			float Weight = NormalDotResult * this->NormalDotScale +
				NormalDistanceResult * this->NormalDistanceScale;
			if (Weight > HighestWeight)
			{
				BestActor = Lap.GetActor();
				HighestWeight = Weight;
			}

			if (bEnableDebugDraw)
			{
				DrawDebugBox(this->GetWorld(),
				             Origin,
				             FVector(50.0f),
				             FColor::Green);

				FString DebugString = FString::Printf(
					TEXT("Weight : %f , Distance : %f , Dot : %f"),
					Weight, NormalDistanceResult, NormalDotResult);

				DrawDebugString(this->GetWorld(),
				                Origin,
				                DebugString,
				                nullptr,
				                FColor::White,
				                .0f,
				                true);
			}
		}

		this->SelectedActor = BestActor;


		if (bEnableDebugDraw)
		{
			if (BestActor != nullptr)
			{
				DrawDebugBox(this->GetWorld(),
				             BestActor->GetActorLocation(),
				             FVector(60.0f),
				             FColor::Blue);
			}
			DrawDebugSphere(this->GetWorld(),
			                Center,
			                this->InteractionRadius,
			                32,
			                FColor::White);
		}
	}
}
