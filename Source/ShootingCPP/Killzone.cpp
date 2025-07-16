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

	//����ƽ���� �����Ǹ� 
	//�� ������ �پ���. ������ ���ȴ�. 
	//��� ��Ÿ���߿� ���� �Ұ����ϴ�
	//��Ÿ���߿� �̵��� �ϸ� ���� ������ �ȹޱ⶧���� ���� ���� �� �ִ�. 
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

