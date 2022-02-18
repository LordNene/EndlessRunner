// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyActor.h"
#include "GameManagerActor.h"
#include "EnemyManagerActor.generated.h"

UENUM()
enum EnemyType
{
	Flying		UMETA(DisplayName = "Flying"),
	Grounded	UMETA(DisplayName = "Grounded")
};

UCLASS()
class RUNNINGAROUND_API AEnemyManagerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManagerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Sets timer for generation of enemies
	void GenerateEnemies();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawnable Enemies")
	TSubclassOf<AEnemyActor> FlyingEnemy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawnable Enemies")
	TSubclassOf<AEnemyActor> GroundedEnemy;

	UPROPERTY(EditAnywhere)
	AActor *PlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Manager")
	AGameManagerActor *GameManager;

	// X coord; How far from the player will be enemies spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Coordinates")
	float SpawnDistanceFlying = 2000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Coordinates")
	float SpawnDistanceGrounded = 1000.0f;
	// The two possible Z coordinates of Spawn Location for the Flying enemies
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Coordinates")
	float FlyingSpawnHeight1 = 150.0f; // Can be jumped over
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Coordinates")
	float FlyingSpawnHeight2 = 300.0f; // Can't be jumped over, can be walked under
	//float FlyingSpawnHeight2 = 250.0f; // Can't be jumped over, can't be dodged (TODO? implement dodging)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Coordinates")
	float GroundedSpawnHeight = 46.0f;
	// Y coord constraints
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Coordinates")
	FVector2D TileRange = { -262.0f, 165.0f };
	
	// Lower and upper bounds for spawn timer
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Timers")
	float SpawnRangeMin = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Timers")
	float SpawnRangeMax = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Timers")
	float SpawnTimer = 1.5f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawnEnemyByType(EnemyType Type);

private:
	void SpawnEnemy(UClass *EnemyToSpawn, FVector SpawnLocation, bool IsMovable);
	void SpawnFlyingEnemy();
	void SpawnGroundedEnemy();

	// Spawns TimerFunctions over randomized time range
	void GenerateSpawnTimers();
	// Spawns flying enemies over a random time interval
	void SpawnTimerFlying();
	// Spawns grounded enemies over a random time interval
	void SpawnTimerGrounded();

	// Timer handle for generating the spawn timers
	FTimerHandle TimerHandleGeneration;
	// Timer handle for spawning flying enemies
	FTimerHandle TimerHandleSpawnFlying;
	// Timer handle for spawning grounded enemies
	FTimerHandle TimerHandleSpawnGrounded;
};
