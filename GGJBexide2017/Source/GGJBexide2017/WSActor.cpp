// Fill out your copyright notice in the Description page of Project Settings.

#include "GGJBexide2017.h"
#include "WSActor.h"


// Sets default values
AWSActor::AWSActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Http = &FHttpModule::Get();
    WebSocket = &FWebSocketsModule::Get();
}

// Called when the game starts or when spawned
void AWSActor::BeginPlay()
{
    TSharedPtr<IWebSocket> ws = WebSocket->CreateWebSocket("ws://taptappun.cloudapp.net:3000/");
    ws->Connect();
    HttpRequest();
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("output : %s"), L"ログの内容");
}

// Called every frame
void AWSActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

/*Http call*/
void AWSActor::HttpRequest()
{
    TSharedRef<IHttpRequest> Request = Http->CreateRequest();
    Request->OnProcessRequestComplete().BindUObject(this, &AWSActor::OnResponseReceived);
    //This is the url on which to process the request
    Request->SetURL("https://google.co.jp");
    Request->SetVerb("GET");
    Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
//    Request->SetHeader("Content-Type", TEXT("application/json"));
    Request->ProcessRequest();
}

/*Assigned function on successfull http call*/
void AWSActor::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    FString stringResponse = Response->GetContentAsString();
    UE_LOG(LogTemp, Warning, TEXT("%s"), *stringResponse);
//    GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, stringResponse);

    //Create a pointer to hold the json serialized data
//    TSharedPtr<FJsonObject> JsonObject;
    
    //Create a reader pointer to read the json data
//    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
    
    //Deserialize the json data given Reader and the actual object to deserialize
//    if (FJsonSerializer::Deserialize(Reader, JsonObject))
//    {
        //Output it to the engine
//        GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, FString::FromInt(recievedInt));
//    }
}
