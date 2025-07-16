// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFactory.h"
#include "Enemy.h"

// Sets default values
AEnemyFactory::AEnemyFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyFactory::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentTime >= DelayTime)
	{

		CurrentTime = 0;
		//스폰 쿨타임보다 현재 시간이 지났다.
		GetWorld()->SpawnActor<AEnemy>(
			EnemyClass, GetActorLocation(),
			GetActorRotation());
	}
	else
	{

		//스폰 쿨타임보다 현재 시간이 낮다면,
		//Deltime 1프레임을 연산하는데 걸린시간
		//currenttime 에 Detatime을 더해준다. 
		CurrentTime += DeltaTime;
	}
}

