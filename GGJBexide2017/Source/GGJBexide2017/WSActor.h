// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "WSActor.generated.h"

UCLASS()
class GGJBEXIDE2017_API AWSActor : public AActor
{
	GENERATED_BODY()

private:
    FHttpModule* Http;
    void HttpRequest(FString url);

public:
    
    /* The actual HTTP call */
    UFUNCTION(BlueprintCallable, Category="WSActor")
    void SendServer();

    UFUNCTION(BlueprintImplementableEvent, Category="WSActor")
    void CallbackResult(const FString& result);
    
    /*Assign this function to call when the GET request processes sucessfully*/
    void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
    
	// Sets default values for this actor's properties
	AWSActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
