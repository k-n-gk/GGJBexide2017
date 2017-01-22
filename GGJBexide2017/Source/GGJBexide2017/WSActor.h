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
    void PlayStart(int32 player);
    
    UFUNCTION(BlueprintCallable, Category="WSActor")
    void SelfPosition(int32 player, FVector position);

    UFUNCTION(BlueprintCallable, Category="WSActor")
    void ReceiveAction(int32 player);

    UFUNCTION(BlueprintCallable, Category="WSActor")
    void Shoot(int32 player, int32 hit_player, int32 hit_zombie_id);

    UFUNCTION(BlueprintCallable, Category="WSActor")
    void Soner(int32 player, FVector position);
    
    UFUNCTION(BlueprintImplementableEvent, Category="WSActor")
    void OnActionResult(int32 action, int32 player, int32 hit_player, int32 hit_zombie_id, float x, float y, float z);
    
    UFUNCTION(BlueprintImplementableEvent, Category="WSActor")
    void OnPositionResult(int32 player, float x, float y, float z);
    
    /*Assign this function to call when the GET request processes sucessfully*/
    void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
    
	// Sets default values for this actor's properties
	AWSActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
