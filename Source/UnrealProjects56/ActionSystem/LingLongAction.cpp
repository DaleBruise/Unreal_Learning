// Fill out your copyright notice in the Description page of Project Settings.


#include "LingLongAction.h"

#include "ActionSystemLingLong.h"
#include "UnrealProjects56.h"

void ULingLongAction::StartAction_Implementation()
{
	this->IsRunningFlag = true;

	float GameTime = this->GetWorld()->TimeSeconds;

	UE_LOGFMT(LogGame, Log, "Start Action {ActionName} - {WorldTime}",
	          ("ActionName", this->ActionName.ToString()),
	          ("WorldTime", GameTime));

	this->GetOwningComponent()->ActiveGameplayTags.AppendTags(this->GrantTags);

	for (auto Cost : this->ActivationCost)
	{
		this->GetOwningComponent()->ApplyAttributeChange(Cost.Key,
		                                                 -Cost.Value,
		                                                 EAttributeModifiedType::Modifier);
	}
}

void ULingLongAction::StopAction_Implementation()
{
	this->IsRunningFlag = false;

	float GameTime = this->GetWorld()->TimeSeconds;

	UE_LOGFMT(LogGame, Log, "Stopped Action {ActionName} - {WorldTime}",
	          ("ActionName", this->ActionName.ToString()),
	          ("WorldTime", GameTime));

	this->CoolDownUntil = this->GetWorld()->TimeSeconds + CoolDownTime;
	this->GetOwningComponent()->ActiveGameplayTags.RemoveTags(this->GrantTags);
}

FGameplayTag ULingLongAction::GetActionName() const
{
	return this->ActionName;
}

bool ULingLongAction::CanStart() const
{
	/* Check if it is still running */
	if (this->IsRunning())
	{
		return false;
	}

	/* Check if the tags are been blocked */
	auto* Pointer = this->GetOwningComponent();
	if (Pointer != nullptr &&
		Pointer->ActiveGameplayTags.HasAny(this->BlockedTags))
	{
		return false;
	}

	/* Check if still has remaining time */
	if (this->GetCoolDownTimeRemaining() > 0.0f)
	{
		return false;
	}
	
	/* Printing the logs */
	UE_LOG(LogGame, Log, TEXT("Cool Down Remaining : %f "), this->GetCoolDownTimeRemaining());
	for (auto Cost : this->ActivationCost)
	{
		float AvailableAttributeAmount = Pointer->GetAttributeValue(Cost.Key);
		if (AvailableAttributeAmount < Cost.Value)
		{
			UE_LOGFMT(LogGame, Log, "Not enough {AttributeName} to activate {ActionName}. "
						   "Have {AvailableAttributeValue} and need {RequiredAttributeValue}",
						   ("AttributeName", Cost.Key.ToString()),
						   ("ActionName", this->ActionName.ToString()),
						   ("AvailableAttributeValue",AvailableAttributeAmount),
						   ("RequiredAttributeValue", Cost.Value));
			return false;
		}
	}
	
	return true;
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
