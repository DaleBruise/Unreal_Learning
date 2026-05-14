// Fill out your copyright notice in the Description page of Project Settings.


#include "LingLongEQS_TargetActor.h"
#include "AIController.h"
#include "LingLongTypes.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"


void ULingLongEQS_TargetActor::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	APawn* QuerierPawn = Cast<APawn>(QueryInstance.Owner.Get());
	check(QuerierPawn);

	auto* Controller = Cast<AAIController>(QuerierPawn->GetController());
	UObject* TargetObject = Controller->GetBlackboardComponent()->
	                                    GetValueAsObject(NAME_TargetActor);
	check(TargetObject)
	auto TargetActor = Cast<AActor>(TargetObject);

	UEnvQueryItemType_Actor::SetContextHelper(ContextData, TargetActor);
}
