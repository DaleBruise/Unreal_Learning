// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LingLongGameplayStatics.generated.h"

class UActionSystemLingLong;
/**
 * 
 */
UCLASS()
class UNREALPROJECTS56_API ULingLongGameplayStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static bool IsFullHealth(UActionSystemLingLong* ActionComp);
};
