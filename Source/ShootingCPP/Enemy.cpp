// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EngineUtils.h"
#include "PlayerPawn.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	SetRootComponent(BoxComp);
	BoxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	BoxComp->SetCollisionProfileName(TEXT("EnemyPreset"));
	


	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static mesh"));
	MeshComp->SetupAttachment(BoxComp);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnEnemyOverlap);

	//FMath :: RandRanges는  첫번째 매개 변수 ~ 두번째 매개 변수까지의 수중 렌덤한 수를 반환해준다.
	//첫번째 매개변수, 두번째 매개변수 포함. 
	int32 DrawResult = FMath::RandRange(1, 100);

	if (DrawResult <= TraceRate)
	{
		//추첨 성공에 대한 로직
		//플레이어를 받아와서
		//내가 플레이러을 바라보는 방향 계산
		//direction 에 계산한 방향 할당
		//접두사 T가 붙는다 템플릿을 활용한 것이다.
		//actor는 월드에 배치될 수 있는 기본 단위, 기본 클래스 
		//iterator는 반복자 , 오브젝트를 인덱싱해서, 인덱스를 증가시키면서 순회 할 수 있는 
		// 템플릿 엑터를 할당할 수 있는 iterator 
		
		//Players는 지금 선언한 TActorIterator<APlayerPawn>의 이름 
		TActorIterator<APlayerPawn>Players(GetWorld());

		if (!Players)
		{

			Direction = GetActorForwardVector();
		}



		//Players에는 현재 월드에 있는 APlayerPawn 타입의 객체들이 담겨 있다.
		//For문은 한번 반복할때마다 Players 안에 있는 AplayerPawn 객체를 순회한다. 
		for (Players; Players; ++Players)
		{// 현재 Players 인덱스인 APlayerpawn 타입의 객체가 
			//이름에 BP_PlayerPawn을 포함하고 있느냐?
			if (Players->GetActorLabel().Contains(TEXT("BP_PlayerPawn0")))
			{
				//현재 Players의 APlayerPawn 타입의 객체의 라벨이 
				//BP_플레이어폰0을 포함합니다. 
				//GetActorLocation() 나의 월드 좌표 
				Direction = Players->GetActorLocation() - this->GetActorLocation();
				//길이가 1로 맞춰짐
				Direction.Normalize();
			}



		}
	}

	else
	{
		// 추첨 실패
		//실패에 대한 로직
		//현재 내가 바라보는 방향을
		Direction = GetActorForwardVector();
		//Direction에 할당 

	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	FVector NewLocation = GetActorLocation() + Direction * MoveSpeed * DeltaTime;

	SetActorLocation(NewLocation);

}

void AEnemy::OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//otheractor가 bullet일 수도 있고, Player일 수 도 있다. 

	APlayerPawn* Crashedplayer = Cast<APlayerPawn>(OtherActor);
	
	if (Crashedplayer) //Crashedplayer != nullptr
	{

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFX, GetActorLocation(), GetActorRotation());

		Crashedplayer->Destroy();
		Destroy();
	}


		
}

