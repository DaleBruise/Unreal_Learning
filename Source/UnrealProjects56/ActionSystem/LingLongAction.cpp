// Fill out your copyright notice in the Description page of Project Settings.


#include "LingLongAction.h"

#include "ActionSystemLingLong.h"

void ULingLongAction::StartAction_Implementation()
{
	this->IsRunningFlag = true;
	
	float GameTime = this->GetWorld()->TimeSeconds;

	UE_LOGFMT(LogTemp, Log, "Start Action {ActionName} - {WorldTime}",
	          ("ActionName", this->ActionName.ToString()),
	          ("WorldTime", GameTime));
}

void ULingLongAction::StopAction_Implementation()
{
	this->IsRunningFlag = false;
	
	float GameTime = this->GetWorld()->TimeSeconds;

	UE_LOGFMT(LogTemp, Log, "Stopped Action {ActionName} - {WorldTime}",
	          ("ActionName", this->ActionName.ToString()),
	          ("WorldTime", GameTime));

	this->CoolDownUntil = this->GetWorld()->TimeSeconds + CoolDownTime;
}

FGameplayTag ULingLongAction::GetActionName() const
{
	return this->ActionName;
}

bool ULingLongAction::CanStart() const
{
	if (this->IsRunning())
	{
		return false;
	}
	
	UE_LOG(LogTemp, Log, TEXT("Cool Down Remaining : %f "), this->GetCoolDownTimeRemaining());
	return this->GetCoolDownTimeRemaining() <= 0.0f;
}

bool ULingLongAction::IsRunning() const
{
	return this->IsRunningFlag;
}

float ULingLongAction::GetCoolDownTimeRemaining() const
{
	return FMath::Max(0.0f, this->CoolDownUntil - this->GetWorld()->TimeSeconds);
}

UActionSystemLingLong* ULingLongAction::GetOwningComponent() const
{
	const auto Pointer = Cast<UActionSystemLingLong>(this->GetOuter());
	return Pointer;
}
