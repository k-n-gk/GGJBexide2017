// Fill out your copyright notice in the Description page of Project Settings.

#include "GGJBexide2017.h"
#include "WSBlueprintFunctionLibrary.h"




FString UWSBlueprintFunctionLibrary::HelloWorld()
{
    return FString("Hello World!!");
}

FString UWSBlueprintFunctionLibrary::HelloWorldInstance()
{
    return FString("Hello World!!");
}

void UWSBlueprintFunctionLibrary::CallDelegate()
{
    OnEventDispather.Broadcast(); // イベントディスパッチャーをCallする
}
