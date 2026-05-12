// Fill out your copyright notice in the Description page of Project Settings.


#include "LingLongAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


ALingLongAIController::ALingLongAIController()
{
	
	PrimaryActorTick.bCanEverTick = true;
}


void ALingLongAIController::BeginPlay()
{
	Super::BeginPlay();
	
	this->RunBehaviorTree(this->BehaviorTree);
	
	
	const FName TargetActor = FName("TargetActor");
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	check(PlayerPawn);
	
	auto ptr = GetBlackboardComponent();
	ptr->SetValueAsObject(TargetActor,
		PlayerPawn);
}
