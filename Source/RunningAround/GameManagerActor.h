// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManagerActor.generated.h"

UCLASS()
class RUNNINGAROUND_API AGameManagerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManagerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float CalculateDistance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Actors")
	AActor *PathGenerator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Actors")
	AActor *PlayerCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Stats")
	float Score = 0.0f; // Distance travelled by Player from the start
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Stats")
	float HighScore = 0.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FVector PreviousLocation;
};
