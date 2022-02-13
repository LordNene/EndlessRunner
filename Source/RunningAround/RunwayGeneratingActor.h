// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Queue.h"
#include "RunwayGeneratingActor.generated.h"

class ATileActor;

UCLASS()
class RUNNINGAROUND_API ARunwayGeneratingActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARunwayGeneratingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Initialize();
	void SpawnTile(AActor *Tile);
	void GeneratePath();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnableTiles")
	AActor *BasicTile;

	UPROPERTY(EditAnywhere)
	AActor *PlayerCharacter;

	FVector TileSize;												 // dimensions
	float PathVanishDistance;										 // distance where tiles should be removed from the back
	int TileVanishLimit = 1.5;										 // distance of PathVanishDistance in amount of tiles
	int QueueLimit = 3;												 // max number of tiles in the queue
	FVector CurrentSpawnLocation = FVector(-39.0f, -47.0f, -300.0f); // initialized to the starting location
	TQueue<ATileActor *> Path;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
