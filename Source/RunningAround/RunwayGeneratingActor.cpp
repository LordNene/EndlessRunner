// Fill out your copyright notice in the Description page of Project Settings.

#include "RunwayGeneratingActor.h"
#include "Engine/StaticMeshActor.h"
#include "TileActor.h"

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
		UE_LOG(LogTemp, Error, TEXT("Didn't set Basic Tile"));
		return;
	}

	FBox TileBounds = BasicTile->GetComponentsBoundingBox();
	TileSize = TileBounds.Max - TileBounds.Min;
	PathVanishDistance = TileSize.X * TileVanishLimit;
	//UE_LOG(LogTemp, Warning, TEXT("TileSize: %f, %f, %f"), TileSize.X, TileSize.Y, TileSize.Z);
}

// Called when the game starts or when spawned
void ARunwayGeneratingActor::BeginPlay()
{
	Super::BeginPlay();

	Initialize();

	//SpawnTile(BasicTile);

	// check if path was already generated (for the first time)
	if (Path.IsEmpty())
	{
		for (int i = 0; i < QueueLimit; i++)
		{
			CurrentSpawnLocation += FVector(TileSize.X, 0.0f, 0.0f);
			SpawnTile(BasicTile);
			//UE_LOG(LogTemp, Warning, TEXT("TileSize: %f, %f, %f"), CurrentSpawnLocation.X, CurrentSpawnLocation.Y, CurrentSpawnLocation.Z);
		}
		return;
	}
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
		UE_LOG(LogTemp, Error, TEXT("Didn't set Player Character"));
		return;
	}

	auto pl = Path.Peek();
	// check if Player's distance from the furthest Tile in the front is smaller than default value
	AActor *LastTile = (*Path.Peek())->GetTile();
	//auto loc = LastTile->GetActorLocation();
	//UE_LOG(LogTemp, Warning, TEXT("Last Tile Loc: %f, %f, %f"), loc.X, loc.Y, loc.Z);
	FVector CurrentSpawnLocationX = FVector(CurrentSpawnLocation.X, 0.0f, 0.0f);
	FVector PlayerCharacterLocationX = FVector(PlayerCharacter->GetActorLocation().X, 0.0f, 0.0f);
	float LastTileDistance = FVector::Dist(CurrentSpawnLocationX, PlayerCharacterLocationX);
	//UE_LOG(LogTemp, Warning, TEXT("Last Tile Dist: %f"), LastTileDistance);
	//UE_LOG(LogTemp, Warning, TEXT("PathVanishDistance: %f"), PathVanishDistance);
	if (LastTileDistance < PathVanishDistance)
	{
		for (int i = 0; i < TileVanishLimit; i++)
		{
			ATileActor *VanishedTile;
			Path.Dequeue(VanishedTile); //TODO object pooling?
			VanishedTile->Vanish();
			CurrentSpawnLocation += FVector(TileSize.X, 0.0f, 0.0f);
			SpawnTile(BasicTile);
		}
	}
}

void ARunwayGeneratingActor::SpawnTile(AActor *Tile)
{
	const FVector SpawnLocation = CurrentSpawnLocation;
	const FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	UClass *TileClass = Tile->GetClass();

	auto NewTile = GetWorld()->SpawnActor(TileClass, &SpawnLocation, &SpawnRotation, SpawnParams);
	// can't just call constructor because it's generated as private in Unreal (the more you know)
	//ATileActor *NewTileActor = NewObject<ATileActor>();
	ATileActor *NewTileActor = static_cast<ATileActor *>(GetWorld()->SpawnActor(ATileActor::StaticClass(), &SpawnLocation, &SpawnRotation, SpawnParams));
	NewTileActor->Init(NewTile, CurrentSpawnLocation);
	Path.Enqueue(NewTileActor);
}
