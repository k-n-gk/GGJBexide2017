// Fill out your copyright notice in the Description page of Project Settings.

#include "GGJBexide2017.h"
#include "WSActor.h"


// Sets default values
AWSActor::AWSActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Http = &FHttpModule::Get();
}

// Called when the game starts or when spawned
void AWSActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("output : %s"), L"ログの内容");
}

// Called every frame
void AWSActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AWSActor::PlayStart(int32 player){
    HttpRequest(FString::Printf(TEXT("http://taptappun.cloudapp.net:3000/playstart?player=%d"),player));
}

void AWSActor::SelfPosition(int32 player, FVector position){
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
    JsonObject->SetNumberField("player", player);
    JsonObject->SetNumberField("x", position.X);
    JsonObject->SetNumberField("y", position.Y);
    JsonObject->SetNumberField("z", position.Z);
    
    FString OutputString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
    if(FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer)){
            HttpRequest(FString::Printf(TEXT("http://taptappun.cloudapp.net:3000/position?info=%s"), *OutputString));
    }
}

void AWSActor::ReceiveAction(int32 player){
    HttpRequest(FString::Printf(TEXT("http://taptappun.cloudapp.net:3000/player_action?player=%d"),player));
}

void AWSActor::Shoot(int32 player, int32 hit_player, int32 hit_zombie_id){
    HttpRequest(FString::Printf(TEXT("http://taptappun.cloudapp.net:3000/player_action?player=%d&hit_player=%d&hit_zombie_id=%d"),player, hit_player, hit_zombie_id));
}

void AWSActor::Soner(int32 player, FVector position){
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
    JsonObject->SetNumberField("player", player);
    JsonObject->SetNumberField("sonar_position_x", position.X);
    JsonObject->SetNumberField("sonar_position_y", position.Y);
    JsonObject->SetNumberField("sonar_position_z", position.Z);
    
    FString OutputString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
    if(FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer)){
        HttpRequest(FString::Printf(TEXT("http://taptappun.cloudapp.net:3000/sonar?info=%s"), *OutputString));
    }
}

/*Http call*/
void AWSActor::HttpRequest(FString url)
{
    TSharedRef<IHttpRequest> Request = Http->CreateRequest();
    Request->OnProcessRequestComplete().BindUObject(this, &AWSActor::OnResponseReceived);
    //This is the url on which to process the request
    Request->SetURL(url);
    Request->SetVerb("GET");
    Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
    Request->SetHeader("Content-Type", TEXT("application/json"));
    Request->ProcessRequest();
}

/*Assigned function on successfull http call*/
void AWSActor::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    FString stringResponse = Response->GetContentAsString();
    UE_LOG(LogTemp, Warning, TEXT("%s"), *stringResponse);
    
    //Create a pointer to hold the json serialized data
    TSharedPtr<FJsonObject> JsonObject;
    
    //Create a reader pointer to read the json data
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
    
    //Deserialize the json data given Reader and the actual object to deserialize
    if (FJsonSerializer::Deserialize(Reader, JsonObject))
    {
        int32 action = JsonObject->GetIntegerField(TEXT("action"));
        if(action == 2){
            OnPositionResult(
                JsonObject->GetIntegerField(TEXT("player")),
                static_cast<float>(JsonObject->GetNumberField(TEXT("x"))),
                static_cast<float>(JsonObject->GetNumberField(TEXT("y"))),
                static_cast<float>(JsonObject->GetNumberField(TEXT("z")))
            );
        }else{
            OnActionResult(
                           action,
                           JsonObject->GetIntegerField(TEXT("player")),
                           JsonObject->GetIntegerField(TEXT("hit_player")),
                           JsonObject->GetIntegerField(TEXT("hit_zombie_id")),
                           static_cast<float>(JsonObject->GetNumberField(TEXT("sonar_position_x"))),
                           static_cast<float>(JsonObject->GetNumberField(TEXT("sonar_position_y"))),
                           static_cast<float>(JsonObject->GetNumberField(TEXT("sonar_position_z")))
                           );
        }
        //Output it to the engine
        //        GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, FString::FromInt(recievedInt));
    }
    
    
//    GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, stringResponse);
}
