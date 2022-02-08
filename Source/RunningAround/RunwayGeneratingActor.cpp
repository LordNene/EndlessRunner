// Fill out your copyright notice in the Description page of Project Settings.


#include "RunwayGeneratingActor.h"
#include "Engine/StaticMeshActor.h"

// Sets default values
ARunwayGeneratingActor::ARunwayGeneratingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// can't be done in constructor, needs to be in BeginPlay because before the BasicTile isn't initialized
void ARunwayGeneratingActor::Initialize()
{
	if (!BasicTile)
	{
		UE_LOG(LogTemp, Warning, TEXT("Didn't set Basic Tile"));
		return;
	}

	FBox TileBounds = BasicTile->GetComponentsBoundingBox();
	TileSize = TileBounds.Max - TileBounds.Min;
	PathVanishDistance = TileSize.X * 3;
	//UE_LOG(LogTemp, Warning, TEXT("TileSize: %f, %f, %f"), TileSize.X, TileSize.Y, TileSize.Z);
}

// Called when the game starts or when spawned
void ARunwayGeneratingActor::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
	
	//SpawnTile(BasicTile);
}

// Called every frame
void ARunwayGeneratingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GeneratePath();
}

void ARunwayGeneratingActor::GeneratePath()
{
	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Didn't set Player Character"));
		return;
	}

	//UE_LOG(LogTemp, Warning, TEXT("AAAAAAAAAAAAAAAA"));

	// check if path was already generated (for the first time)
	if (Path.IsEmpty())
	{
		for (int i = 0; i < QueueLimit; i++)
		{
			CurrentSpawnLocation += FVector(TileSize.X, 0.0f, 0.0f);
			SpawnTile(BasicTile);
			UE_LOG(LogTemp, Warning, TEXT("TileSize: %f, %f, %f"), CurrentSpawnLocation.X, CurrentSpawnLocation.Y, CurrentSpawnLocation.Z);
		}
		return;
	}
	
	// check if Player's distance from the furthest Tile in the back is greater than default value
	AActor* LastTile = *Path.Peek();
	float LastTileDistance = FVector::Dist(LastTile->GetActorLocation(), PlayerCharacter->GetActorLocation());
	if (LastTileDistance > PathVanishDistance)
	{
		for (int i = 0; i < PathVanishDistance; i++)
		{
			AActor* VanishedTile;
			Path.Dequeue(VanishedTile); //TODO just pop? but maybe I could reuse it
			CurrentSpawnLocation += FVector(TileSize.X, 0.0f, 0.0f);
			SpawnTile(BasicTile);
		}
	}

}

void ARunwayGeneratingActor::SpawnTile(AActor* Tile)
{
	const FVector SpawnLocation = CurrentSpawnLocation;
	const FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	UClass* TileClass = Tile->GetClass();

	GetWorld()->SpawnActor(TileClass, &SpawnLocation, &SpawnRotation, SpawnParams);
}

