// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManagerActor.h"
#include "Engine/Blueprint.h"

// Sets default values
AEnemyManagerActor::AEnemyManagerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyManagerActor::BeginPlay()
{
	Super::BeginPlay();
	
	GenerateEnemies();
}

// Sets a timer to spawn enemies every few seconds
void AEnemyManagerActor::GenerateEnemies()
{
	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("Didn't set Player Character"));
		return;
	}

	if (!FlyingEnemy)
	{
		UE_LOG(LogTemp, Error, TEXT("Didn't set an enemy blueprint."));
		return;
	}

	// Calls timer every {SpawnTimer} seconds, first one is delayed for 7 seconds
	GetWorldTimerManager().SetTimer(TimerHandleGeneration, this, &AEnemyManagerActor::GenerateSpawnTimers, SpawnTimer, true, 7.0f);
}

void AEnemyManagerActor::GenerateSpawnTimers()
{
	float SpawnRange = FMath::RandRange(SpawnRangeMin, SpawnRangeMax);
	GetWorldTimerManager().SetTimer(TimerHandleSpawn, this, &AEnemyManagerActor::SpawnTimerFunction, SpawnRange, false, 0.0f);
	//UE_LOG(LogTemp, Warning, TEXT("Spawn interval: %f"), SpawnRange);
}

void AEnemyManagerActor::SpawnTimerFunction()
{
	SpawnEnemy(EnemyType::Flying);
}

// Called every frame
void AEnemyManagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyManagerActor::SpawnEnemy(EnemyType Type)
{
	FVector SpawnLocation = PlayerCharacter->GetActorLocation();
	SpawnLocation.X += SpawnDistance;
	// Turn enemy to face the player
	FRotator SpawnRotation = PlayerCharacter->GetActorRotation();
	SpawnRotation.Yaw += 180;
	FActorSpawnParameters SpawnParams;

	AEnemyActor* EnemyRef = GetWorld()->SpawnActor<AEnemyActor>(FlyingEnemy, SpawnLocation, SpawnRotation, SpawnParams);
	// Set GameManager reference so collision can be handled in BP
	EnemyRef->Initialize(GameManager, PlayerCharacter);
}

