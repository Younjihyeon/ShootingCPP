// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPCBase.h"
#include "Bullet.generated.h"

UCLASS()
class SHOOTINGCPP_API ABullet : public ANPCBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnNPCOverlap(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;
};
