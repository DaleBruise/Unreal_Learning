// Fill out your copyright notice in the Description page of Project Settings.


#include "LingLongAction_Projectile.h"
#include "LingLongTypes.h"
#include "ActionSystemLingLong.h"
#include "NiagaraFunctionLibrary.h"

#include "GameFramework/Character.h"

#include "Kismet/GameplayStatics.h"

#include "Projectiles/ProjectileBase.h"

ULingLongAction_Projectile::ULingLongAction_Projectile()
{
	this->MuzzleSocketName = TEXT("Muzzle_01");
}

void ULingLongAction_Projectile::StartAction()
{
	Super::StartAction();

	/* Setting the attack animation and sound */
	UActionSystemLingLong* ActionComp = this->GetOwningComponent();
	check(ActionComp);
	ACharacter* Character = Cast<ACharacter>(ActionComp->GetOwner());
	check(Character);

	Character->PlayAnimMontage(this->AttackMontage);

	UNiagaraFunctionLibrary::SpawnSystemAttached(this->CastingEffect,
	                                             Character->GetMesh(),
	                                             this->MuzzleSocketName,
	                                             FVector::ZeroVector,
	                                             FRotator::ZeroRotator,
	                                             EAttachLocation::Type::SnapToTarget,
	                                             true);

	UGameplayStatics::PlaySound2D(this,
	                              this->CastingSound);

	FTimerHandle TimerHandle_PrimaryAttack;
	float AttackAnimDelay = 0.2f;
	this->GetWorld()->GetTimerManager().SetTimer(TimerHandle_PrimaryAttack,
	                                             this,
	                                             &ThisClass::AttackTimerElapsed,
	                                             AttackAnimDelay,
	                                             false);
}

void ULingLongAction_Projectile::AttackTimerElapsed()
{
	UActionSystemLingLong* ActionComp = this->GetOwningComponent();
	check(ActionComp);
	ACharacter* Character = Cast<ACharacter>(ActionComp->GetOwner());
	check(Character);

	/* Setting the projectile location */
	FVector SpawnLocation = Character->GetMesh()->GetSocketLocation(this->MuzzleSocketName);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = Character;

	/* Optimize the projectile's direction */
	FVector EyeLocation;
	FRotator EyeRotation;
	Character->GetController()->GetPlayerViewPoint(EyeLocation, EyeRotation);
	FVector TraceEnd = EyeLocation + (EyeRotation.Vector() * 5000.0f);

	FHitResult Hit;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Character);

	FVector AdjustedTargetLocation;
	if (this->GetWorld()->LineTraceSingleByChannel(Hit,
	                                               EyeLocation,
	                                               TraceEnd,
	                                               COLLISION_PROJECTILE,
	                                               CollisionParams))
	{
		AdjustedTargetLocation = Hit.Location;
	}
	else
	{
		AdjustedTargetLocation = TraceEnd;
	}

	FRotator SpawnRotation = (AdjustedTargetLocation - SpawnLocation).Rotation();

	AActor* NewProjectile = this->GetWorld()->SpawnActor<AActor>(
		this->ProjectileClass,
		SpawnLocation,
		SpawnRotation,
		SpawnParams);

	Character->MoveIgnoreActorAdd(NewProjectile);

	/* Debug stuff */
	if (CVarInteractionDebugDrawing.GetValueOnGameThread())
	{
		float DebugDrawDuration = 5.0f;
		DrawDebugBox(this->GetWorld(),
		             AdjustedTargetLocation,
		             FVector(20.0f),
		             FColor::Green,
		             false,
		             DebugDrawDuration);

		DrawDebugLine(this->GetWorld(),
		              EyeLocation,
		              TraceEnd,
		              FColor::Green,
		              false,
		              DebugDrawDuration);

		DrawDebugLine(this->GetWorld(),
		              SpawnLocation,
		              AdjustedTargetLocation,
		              FColor::Yellow,
		              false,
		              DebugDrawDuration);

		DrawDebugLine(this->GetWorld(),
		              SpawnLocation,
		              SpawnLocation + (EyeRotation.Vector() * 5000.0f),
		              FColor::Purple,
		              false,
		              DebugDrawDuration);
	}
}
