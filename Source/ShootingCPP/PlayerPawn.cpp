// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Bullet.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// CreateDefaultSubobject 클래스를 객체화 하는 함수 
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));

	//SetRootComponent 이 객체의 rootComponent로 매개변수에 들어온 컴포턴트를 지정한다. 
	SetRootComponent(BoxComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Mesh Component"));

	//매개변수에 넣은 컴포넌트의 자식으로 설정한다. 
	MeshComp->SetupAttachment(BoxComp);

	//간접 연산좌 -> 내부 변수나 기능으로 접근
	//xyz값을 넣을 수 있는 구조체 
	FVector BoxSize = FVector(50.0f, 50.0f, 50.0f);

	//BoxComp의 BoxExtent를 매개변수로 FVector 값으로 설정한다. 
	BoxComp->SetBoxExtent(BoxSize);

	BoxComp->SetGenerateOverlapEvents(true);
	//OverlapEvents를 사용할수 있게 true로 설정
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	//CollisionObject = player
	BoxComp->SetCollisionObjectType(ECC_GameTraceChannel1);
	BoxComp->SetCollisionResponseToAllChannels(ECR_Ignore);

	BoxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel2,ECR_Overlap);

	// CreateDefaultSubobject
	// 템플릿 <> 안에 들어온 타입을 객체화 (할당) 한다. 
	// ()즉 매개 변수 컴포넌트의 이름을 뜻한다. 
	// 반환 값은 템플렛 <> 안에 들어온 타입의 객체의 주소값 
	FirePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("Fire Pos"));
	FirePosition->SetupAttachment(BoxComp);

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	//GetWorld 현재 실행중인 Uworld를 반환한다. 
	// PlayerController0 이 반환된다. 

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	//check는 PlayerController가 유효하지 않다면 크래쉬를 낸다. 
	check(PlayerController);

	//PlayerController 0 번에 있는 LocalPlayer의 
	//UEnhancedInputLocalPlayerSubsystem을 가져오는 작업 
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
	ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>
		(PlayerController->GetLocalPlayer());

	check(Subsystem);
	// 서브시스템에 맵핑해도 인풋MappingContext를 추가해준다. 
	//즉 우리가 맵핑한 입력 맵을 추가해준다. 
	//0은 우선순위가 0번 즉 우선순위가 가장 높다는 이야기
	Subsystem->AddMappingContext(IMC_PlayerInput, 0);


}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector dir = FVector(0, Horizontal, Vertical);
	dir.Normalize(); //fvector 길이가 1로 정규화 된다. 

	// GetActorLocation은 나의 월드 좌표를 반환한다. 
	FVector NewLocation = GetActorLocation() + dir * MoveSpeed * DeltaTime;

	//SetActorLocation은 나의 월드 좌표를 매개 변수로 들어온
	//fvector의 값으로 바꾼다. 

	SetActorLocation(NewLocation);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	
	UEnhancedInputComponent* EnhancedInputComponent =
		Cast<UEnhancedInputComponent>(PlayerInputComponent);

	check(EnhancedInputComponent);

	//ETriggerEvent로 Mode 를 설정할 수 있다. 
	//this는 나 자신을 의미 한다. 즉 AplayerPawnCompleted
	// 발동 될 함수 주소  APlayerPawn::OnInputVertical
	EnhancedInputComponent->BindAction(IA_Horizontal, ETriggerEvent::Triggered, this , &APlayerPawn::OnInputHorizontal);
	EnhancedInputComponent->BindAction(IA_Horizontal, ETriggerEvent::Completed, this, &APlayerPawn::OnInputHorizontal);
	EnhancedInputComponent->BindAction(IA_Vertical, ETriggerEvent::Triggered, this, &APlayerPawn::OnInputVertical);
	EnhancedInputComponent->BindAction(IA_Vertical, ETriggerEvent::Completed, this, &APlayerPawn::OnInputVertical);

	EnhancedInputComponent->BindAction(IA_Fire, ETriggerEvent::Started, this, &APlayerPawn::Fire);
}

void APlayerPawn::OnInputHorizontal(const FInputActionValue& value)
{
	Horizontal = value.Get<float>();
	// UE_LOG(LogTemp, Warning, TEXT("Horizontal : % 2f"), Horizontal);

}

void APlayerPawn::OnInputVertical(const FInputActionValue& value)
{
	Vertical = value.Get<float>();
	// UE_LOG(LogTemp, Warning, TEXT("Vertical : % 2f"), Vertical);

}

void APlayerPawn::Fire()
{
	//현재 활성화 있는 uworld를 반환한다. 

	UWorld* CurrentWorld = GetWorld();
	check(CurrentWorld);

	//bulletfactory에 엔진에서 BP_Bullet_C(class)를 할당해줬다. 
	//다형성이 사용됐다. 
	// ABullet*에 BP_Bullet알맹이를 가진 ABullet* 타입을 넣었다. 
	// SpawnActor 두번째 매개 변수에는 생성될 월드 좌표
	// SpawnActor 세번째 매개변수에는 생성될 회전값 
	ABullet* Newbullet = CurrentWorld->SpawnActor<ABullet>(BulletFactory,
	FirePosition -> GetComponentLocation(), FirePosition-> GetComponentRotation());

}

