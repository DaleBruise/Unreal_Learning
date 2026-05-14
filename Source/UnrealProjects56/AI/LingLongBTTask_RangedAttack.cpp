// Fill out your copyright notice in the Description page of Project Settings.


#include "LingLongBTTask_RangedAttack.h"
#include "AIController.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "Projectiles/ProjectileBase.h"

#include "GameFramework/Character.h"

EBTNodeResult::Type
ULingLongBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
                                          uint8* NodeMemory)
{
	auto* Pawn = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn());
	check(Pawn);

	FVector SpawnLocation = Pawn->GetMesh()->GetSocketLocation(this->MuzzleSocketName);
	auto Ptr = OwnerComp.GetBlackboardComponent();
	check(Ptr)

	auto TargetObject = Ptr->GetValueAsObject(this->TargetActorKey.SelectedKeyName);
	if (!IsValid(TargetObject))
	{
		return EBTNodeResult::Failed;
	}
	auto TargetActor = Cast<AActor>(TargetObject);

	FVector Direction = TargetActor->GetActorLocation() - SpawnLocation;
	FRotator SpawnRotation = Direction.Rotation();
	SpawnRotation.Pitch += FMath::FRandRange(0.0f, this->MaxBulletSpread);
	SpawnRotation.Yaw += FMath::FRandRange(-this->MaxBulletSpread, this->MaxBulletSpread);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = Pawn;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto NewProj = this->GetWorld()->SpawnActor<AActor>(this->ProjectileClass,
	                                                    SpawnLocation,
	                                                    SpawnRotation,
	                                                    SpawnParams);
	
	return NewProj != nullptr ? 
		EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}
