// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileActor.generated.h"

UCLASS()
class RUNNINGAROUND_API ATileActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATileActor();
	// initializes Tile's values
	void Init(AActor *NewTile, FVector CurrentSpawnLocation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool IsAtTargetLocation();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	AActor *GetTile();
	void Vanish();

private:
	AActor *Tile;
	bool IsMoving = true;		// defaultly set to true because it should move up after spawning
	bool IsVanishing = false;	// if tile should be destroyed
	float UpperBound = 3.0f;	// upper destination for tile - where it wants to end up after spawning
	float LowerBound = -300.0f; // lower destination, where tiles vanish (Z distance from spawn location where tiles spawn)
	float MovingSpeed = 2.0f;
	FVector TargetLocation;
	FVector SpawnLocation;
};
