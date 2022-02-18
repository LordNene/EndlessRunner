// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManagerActor.h"
#include "EnemyActor.generated.h"

UCLASS()
class RUNNINGAROUND_API AEnemyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Move();
	// Checks if the enemy is behind the player where it can disappear
	bool IsInVanishDistance(float EnemyLocationX);
	void Vanish();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Initialize(AGameManagerActor *GameManagerRef, AActor *PlayerCharacterRef, bool Movable);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Manager")
	AGameManagerActor *GameManager;
	AActor *PlayerCharacter;

private:
	bool IsMovable = true;
	float MovingSpeed = 3.0f;
	float VanishingDistance = 1000.0f;
};
