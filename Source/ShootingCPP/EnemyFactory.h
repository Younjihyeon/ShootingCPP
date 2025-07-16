// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyFactory.generated.h"

UCLASS()
class SHOOTINGCPP_API AEnemyFactory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyFactory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//스폰 딜레이타임
	UPROPERTY(EditAnywhere)
	float DelayTime = 2.0f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemy> EnemyClass;

private:
	//현재 시간
	float CurrentTime;

};
