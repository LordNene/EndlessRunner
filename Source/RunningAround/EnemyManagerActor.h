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
	Flying	UMETA(DisplayName = "Flying")
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

	UPROPERTY(EditAnywhere)
	AActor *PlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Manager")
	AGameManagerActor* GameManager;

	// How far from the player will be enemies spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Constants")
	float SpawnDistance = 2000.0f;
	// Lower and upper bounds for spawn timer
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Constants")
	float SpawnRangeMin = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Constants")
	float SpawnRangeMax = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Constants")
	float SpawnTimer = 3.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawnEnemy(EnemyType Type);

	// Spawns enemies over a random time interval
	void SpawnTimerFunction();
	// Timer handle for spawning enemies
	FTimerHandle TimerHandle;
};
