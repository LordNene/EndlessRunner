// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManagerActor.h"
//#include "Runtime/Engine/Public/EngineGlobals.h"

// Sets default values
AGameManagerActor::AGameManagerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameManagerActor::BeginPlay()
{
	Super::BeginPlay();
	
	// Set initial value for distance calculation
	PreviousLocation = PlayerCharacter->GetActorLocation();
	StartingLocationZ = PreviousLocation.Z;
}

// Called every frame
void AGameManagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Score += CalculateDistance();
	//GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Green, FString::Printf(TEXT("Score: %f"), Score));
}

// Distance travelled in meters = score for the game
float AGameManagerActor::CalculateDistance()
{
	FVector CurrentLoc = PlayerCharacter->GetActorLocation();
	FVector Distance = PreviousLocation - CurrentLoc; // Distance in cm
	PreviousLocation = CurrentLoc;
	return Distance.Size() / 100; // Distance in m
}

void AGameManagerActor::GameOver()
{
	// Saving and loading of High score is handled in Blueprints
	// Keeping this method for the future
}

// Check if player got hit by an enemy or has fallen from the path into the pit
bool AGameManagerActor::IsPlayerDead()
{
	// Right now, the player starts a bit above the tile, but the idea is to let player
	// fall down a bit so it can be buffered by high enough offset
	return WasPlayerHit || PlayerCharacter->GetActorLocation().Z < StartingLocationZ - LocationZOffset;
}