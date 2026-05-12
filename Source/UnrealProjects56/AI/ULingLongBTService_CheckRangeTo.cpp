// Fill out your copyright notice in the Description page of Project Settings.


#include "ULingLongBTService_CheckRangeTo.h"
#include "AIController.h"

#include "BehaviorTree/BlackboardComponent.h"

void UULingLongBTService_CheckRangeTo::TickNode(UBehaviorTreeComponent& OwnerComp,
                                                uint8* NodeMemory,
                                                float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const auto Ptr = OwnerComp.GetBlackboardComponent();
	check(Ptr)
	auto* BBComp = Ptr->GetValueAsObject(this->TargetActorKey.SelectedKeyName);
	check(BBComp)
	const auto TargetActor = Cast<AActor>(BBComp);

	const FVector TargetLocation = TargetActor->GetActorLocation();
	auto Controller = OwnerComp.GetAIOwner();
	if (Controller != nullptr)
	{
		APawn* OwningPawn = Controller->GetPawn();
		check(OwningPawn)
		FVector OriginLocation = OwningPawn->GetActorLocation();

		float DistanceTo = FVector::Dist(
			TargetLocation,
			OriginLocation);
		bool IfWithinRange = DistanceTo < this->MaxAttackRange;
aa
		bool IfHasLOS = Controller->LineOfSightTo(TargetActor);
		
		Ptr->SetValueAsBool(this->WithinRangeKey.SelectedKeyName,
		                    IfWithinRange && IfHasLOS);
	}
}
