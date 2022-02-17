// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemyActor::Initialize(AGameManagerActor *GameManagerRef, AActor *PlayerCharacterRef)
{
	GameManager = GameManagerRef;
	PlayerCharacter = PlayerCharacterRef;
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move();
}

void AEnemyActor::Move()
{
	FVector NewLocation = this->GetActorLocation();
	NewLocation.X -= MovingSpeed;

	if (PlayerCharacter && IsInVanishDistance(NewLocation.X))
	{
		Vanish();
	}

	this->SetActorLocation(NewLocation);
}

bool AEnemyActor::IsInVanishDistance(float EnemyLocationX)
{
	return EnemyLocationX < (PlayerCharacter->GetActorLocation().X - VanishingDistance);
}

void AEnemyActor::Vanish()
{
	// TODO handle vanishing using object pooling
	Destroy();
}