// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "WSBlueprintFunctionLibrary.generated.h"

// 動的マルチキャストデリゲート(イベントディスパッチャー)の宣言
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMyActorOnEventDispather);

/**
 * 
 */
UCLASS()
class GGJBEXIDE2017_API UWSBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


public:
    UFUNCTION(BlueprintCallable, Category="WSBlueprintFunctionLibrary")
    static FString HelloWorld();
    
    UFUNCTION(BlueprintCallable, Category="WSBlueprintFunctionLibrary")
    FString HelloWorldInstance();
    
    void CallDelegate();

    // 動的マルチキャストデリゲート(イベントディスパッチャー)の定義
    UPROPERTY(BlueprintAssignable, Category="WSBlueprintFunctionLibrary")
    FMyActorOnEventDispather OnEventDispather;
	
};
