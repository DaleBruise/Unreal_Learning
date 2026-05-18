// Fill out your copyright notice in the Description page of Project Settings.


#include "LingLongAction.h"

void ULingLongAction::StartAction()
{
	float GameTime = 0.5f;
	
	UE_LOGFMT(LogTemp, Log, "Start Action {ActionName} - {WorldTime}",
		("ActionName", this->ActionName),
		("WorldTime", GameTime));
}

FName ULingLongAction::GetActionName() const
{
	return this->ActionName;
}
