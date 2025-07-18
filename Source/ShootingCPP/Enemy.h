﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class SHOOTINGCPP_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere)
	int32 TraceRate = 50;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 800.0f;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* explosionFX;


	UFUNCTION()
	void OnEnemyOverlap
	(UPrimitiveComponent* OverlappedComponent,
	 AActor* OtherActor, 
	 UPrimitiveComponent* OtherComp,
	 int32 OtherBodyIndex,
	 bool bFromSweep,
	const FHitResult& SweepResult);
	
private:
	FVector Direction; 
	//방향 벡터를 할당 할 예정

};
