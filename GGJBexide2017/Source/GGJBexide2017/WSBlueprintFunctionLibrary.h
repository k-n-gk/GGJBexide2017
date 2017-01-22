// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "WSBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GGJBEXIDE2017_API UWSBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	
    UFUNCTION(BlueprintCallable, Category="WSBlueprintFunctionLibrary")
    static FString HelloWorld();
	
};
