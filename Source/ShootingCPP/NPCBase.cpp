// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystem.h"

// Sets default values
ANPCBase::ANPCBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));
	SetRootComponent(BoxComp);
	BoxComp->SetBoxExtent(FVector::One() * 50.0f);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Mesh Component"));
	MeshComp->SetupAttachment(BoxComp);


	//��θ� ���� �����ؼ� cubemesh�� C++�������� ����Ϸ��� �ڵ�
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMesh.Succeeded()) //��θ� ����� ã�Ƽ� ������Ʈ�� �������� �� �Ϸ��ߴٸ� true
	{
		MeshComp->SetStaticMesh(CubeMesh.Object);

	}


	static ConstructorHelpers::FObjectFinder<UStaticMesh> DroneMesh(TEXT("/Game/ShootingCPP/Modeling/Drone/Drone_low.Drone_low"));
	if (DroneMesh.Succeeded())
	{
		MeshComp->SetStaticMesh(DroneMesh.Object);

	}
	static ConstructorHelpers::FObjectFinder<UMaterial> DroneMat(TEXT("/Game/ShootingCPP/Modeling/Drone/Material__24.Material__24"));
	if (DroneMat.Succeeded())
	{
		MeshComp->GetStaticMesh()->SetMaterial(0, DroneMat.Object);

	}









	/*static ConstructorHelpers::FObjectFinder<UMaterial> BasicMaterial(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
	if (BasicMaterial.Succeeded())
	{

		MeshComp->GetStaticMesh()->SetMaterial(0, BasicMaterial.Object);

	}*/
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ExplosionFXFinder(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
	if (ExplosionFXFinder.Succeeded())
	{
		explosionFX = ExplosionFXFinder.Object;
	}





}

// Called when the game starts or when spawned
void ANPCBase::BeginPlay()
{
	Super::BeginPlay();
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ANPCBase::OnNPCOverlap);
}

// Called every frame
void ANPCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

