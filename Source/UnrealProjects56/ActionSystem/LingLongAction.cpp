// Fill out your copyright notice in the Description page of Project Settings.


#include "LingLongAction.h"

#include "ActionSystemLingLong.h"

void ULingLongAction::StartAction_Implementation()
{
	float GameTime = this->GetWorld()->TimeSeconds;
	
	UE_LOGFMT(LogTemp, Log, "Start Action {ActionName} - {WorldTime}",
		("ActionName", this->ActionName),
		("WorldTime", GameTime));
}

void ULingLongAction::StopAction_Implementation()
{
	float GameTime = this->GetWorld()->TimeSeconds;
	
	UE_LOGFMT(LogTemp, Log, "Stopped Action {ActionName} - {WorldTime}",
		("ActionName", this->ActionName),
		("WorldTime", GameTime));
}

FName ULingLongAction::GetActionName() const
{
	return this->ActionName;
}

UActionSystemLingLong* ULingLongAction::GetOwningComponent() const
{
	const auto Pointer = Cast<UActionSystemLingLong>(this->GetOuter());
	return Pointer;
}