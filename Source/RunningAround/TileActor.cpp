// Fill out your copyright notice in the Description page of Project Settings.

#include "TileActor.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ATileActor::ATileActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Sets this Tile's values
void ATileActor::Init(AActor *NewTile, FVector CurrentSpawnLocation)
{
	Tile = NewTile;
	SpawnLocation = CurrentSpawnLocation;
	TargetLocation = FVector(CurrentSpawnLocation.X, CurrentSpawnLocation.Y, UpperBound);
	IsMoving = true;
}

// Called when the game starts or when spawned
void ATileActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsMoving)
	{
		FVector NewLocation = FMath::VInterpTo(Tile->GetActorLocation(), TargetLocation, DeltaTime, MovingSpeed);
		Tile->SetActorLocation(NewLocation);
		UE_LOG(LogTemp, Warning, TEXT("Moving to: %f"), NewLocation.Z);
		if (IsAtTargetLocation())
		{
			IsMoving = false;
		}
	}

	if (IsVanishing && !IsMoving)
	{
		Tile->Destroy();
		this->Destroy();
	}
}

void ATileActor::Vanish()
{
	IsVanishing = true;
	IsMoving = true;
	TargetLocation.Z = LowerBound;
}

bool ATileActor::IsAtTargetLocation()
{
	return Tile->GetActorLocation().Z == TargetLocation.Z;
}

AActor *ATileActor::GetTile()
{
	return Tile;
}