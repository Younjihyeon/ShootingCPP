// Fill out your copyright notice in the Description page of Project Settings.


#include "Killzone.h"
#include "Components/BoxComponent.h"
// Sets default values
AKillzone::AKillzone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	SetRootComponent(BoxComp);

	//스테틱으로 설정되면 
	//즉 연산이 줄어든다. 성능이 향상된다. 
	//대신 런타임중에 생성 불가능하다
	//런타임중에 이동을 하면 조명 영향을 안받기때문에 이질 적일 수 있다. 
	BoxComp->SetMobility(EComponentMobility::Static);
	BoxComp->SetBoxExtent(FVector(50, 2000, 50));
	BoxComp->SetCollisionProfileName(TEXT("Killzone"));
}

// Called when the game starts or when spawned
void AKillzone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKillzone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

