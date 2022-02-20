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

	if (!FlyingEnemy || !GroundedEnemy)
	{
		UE_LOG(LogTemp, Error, TEXT("Didn't set an enemy blueprint."));
		return;
	}

	// Calls timer every {SpawnTimer} seconds, first one is delayed for 7 seconds
	GetWorldTimerManager().SetTimer(TimerHandleGeneration, this, &AEnemyManagerActor::GenerateSpawnTimers, SpawnTimer, true, 7.0f);
}

void AEnemyManagerActor::GenerateSpawnTimers()
{
	float SpawnRangeGrounded = FMath::RandRange(SpawnRangeMin, SpawnRangeMax);
	GetWorldTimerManager().SetTimer(TimerHandleSpawnGrounded, this, &AEnemyManagerActor::SpawnTimerGrounded, SpawnRangeGrounded, false, 0.0f);
	float SpawnRangeFlying = FMath::RandRange(SpawnRangeMin, SpawnRangeMax);
	GetWorldTimerManager().SetTimer(TimerHandleSpawnFlying, this, &AEnemyManagerActor::SpawnTimerFlying, SpawnRangeFlying, false, 0.0f);
	//UE_LOG(LogTemp, Warning, TEXT("Spawn interval: %f"), SpawnRange);
}

void AEnemyManagerActor::SpawnTimerFlying()
{
	SpawnEnemyByType(EnemyType::Flying);
}

void AEnemyManagerActor::SpawnTimerGrounded()
{
	SpawnEnemyByType(EnemyType::Grounded);
}

// Called every frame
void AEnemyManagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyManagerActor::SpawnEnemyByType(EnemyType Type)
{
	switch (Type)
	{
		case EnemyType::Flying:
			SpawnFlyingEnemy();
			break;
		case EnemyType::Grounded:
			SpawnGroundedEnemy();
			break;
	}
}

void AEnemyManagerActor::SpawnFlyingEnemy()
{
	FVector SpawnLocation = PlayerCharacter->GetActorLocation();
	SpawnLocation.X += SpawnDistanceFlying;

	// Randomize Y Location
	float YRange = FMath::RandRange(TileRange[0], TileRange[1]);
	SpawnLocation.Y = YRange;

	// Pick one of the spawn heights at random
	int Height = rand() % 2;
	SpawnLocation.Z = Height == 0 ? FlyingSpawnHeight1 : FlyingSpawnHeight2;

	SpawnEnemy(FlyingEnemy, SpawnLocation, true);
}

void AEnemyManagerActor::SpawnGroundedEnemy()
{
	FVector SpawnLocation = PlayerCharacter->GetActorLocation();
	SpawnLocation.X += SpawnDistanceGrounded;

	// Randomize Y Location
	float YRange = FMath::RandRange(TileRange[0], TileRange[1]);
	SpawnLocation.Y = YRange;

	// Use default Z Location for grounded enemies
	SpawnLocation.Z = GroundedSpawnHeight;

	// for now, grounded enemies shouldn't move
	SpawnEnemy(GroundedEnemy, SpawnLocation, false);
}

void AEnemyManagerActor::SpawnEnemy(UClass *EnemyToSpawn, FVector SpawnLocation, bool IsMovable)
{
	// Turn enemy to face the player
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnParams;

	AEnemyActor* EnemyRef = GetWorld()->SpawnActor<AEnemyActor>(EnemyToSpawn, SpawnLocation, SpawnRotation, SpawnParams);
	// Set GameManager reference so collision can be handled in BP
	EnemyRef->Initialize(GameManager, PlayerCharacter, IsMovable);
}