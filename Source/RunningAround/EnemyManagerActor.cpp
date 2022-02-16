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
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemyManagerActor::SpawnTimerFunction, SpawnTimer, true, 7.0f);
}

void AEnemyManagerActor::SpawnTimerFunction()
{
	SpawnEnemy(EnemyType::Flying);
}

// Called every frame
void AEnemyManagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//float SpawnRange = FMath::RandRange(SpawnRangeMin, SpawnRangeMax);
	
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
}

