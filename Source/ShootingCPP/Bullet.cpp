// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Enemy.h"


// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));
	SetRootComponent(BoxComp);
	BoxComp->SetBoxExtent(FVector::One() * 50.0f);
	BoxComp->SetWorldScale3D(FVector(0.75f, 0.25f, 1.0f));
	BoxComp->SetCollisionProfileName(TEXT("BulletPreset"));


	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Mesh Component"));
	MeshComp->SetupAttachment(BoxComp);
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBulletOverlap);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// GetActorLocation 월드 기준 내 좌표를 반환
	// GetActorForwardVector 내가 바라보고 있는 방향 벡터를 반환 

	FVector NewLocation = GetActorLocation() + GetActorForwardVector() * MoveSpeed * DeltaTime;
	// SetActorLocation 매개 변수로 들어온 벡터로 내 월드 좌표를 이동 시킨다. 
	SetActorLocation(NewLocation);
}

//어떤 Actor랑 오버랩이 되면 발동한다.
void ABullet::OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//나랑 상호작용한 Actor가 OtherActor로 주어진다.
	AEnemy* CrashedEnemy = Cast<AEnemy>(OtherActor);
	
	//CrashedEnemy가 유효 하다면 
	//CrashedEnemy를 파괴한다. 
	if (CrashedEnemy != nullptr)
	{
		//GetActortransform 나의 transform을 반환
		
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFX, GetActorLocation(), GetActorRotation());


		CrashedEnemy->Destroy();
	}

	Destroy();

}

