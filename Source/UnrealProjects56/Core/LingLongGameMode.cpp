// Fill out your copyright notice in the Description page of Project Settings.


#include "LingLongGameMode.h"

#include "Player/LingLongPlayerController.h"

ALingLongGameMode::ALingLongGameMode()
{
	this->PlayerControllerClass = ALingLongPlayerController::StaticClass(); /* Derived from GameModeBase class*/
}
