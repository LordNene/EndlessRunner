// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
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
	void Initialize();
	void Move();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	float MovingSpeed = 3.0f;
};
