// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "PlayerPawn.generated.h"


UCLASS()
class SHOOTINGCPP_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	//생성자 함수 : 객체화 될 때 어떤 함수보다 먼저 실행된다.
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	// 플레이 버튼을 누를때 혹은, 객체가 생성 될때 1번 
	virtual void BeginPlay() override;

public:	
	// Called every frame
	// 매 프레임 마다 실행 되는 함수 이다. deltatime 한프레임을 연산하는데 걸린시간
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	//전방 선언 
	// 선언할 타입 앞에 class를 붙이면 
	// 이뒤에 올 타입이 class타입이라고 컴퓨터가 알고 있는다. 
	//UBoxComponent는 엔진에서 boxcollision과 같다.
	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComp;
	//표면을 그릴 수 있는 컴포넌트.
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComp;

	



	UPROPERTY(EditAnywhere)
	class UArrowComponent* FirePosition;

	//T접두사는 템플릿을 의미한다. 
	//템플릿이란 제작당시에 타입을 지정하지 않고, 
	//사용할때 타입을 지정할 수 있는 기능
	///TSubclassOf <> 안에 들어온 클래스와 
	//그 자식 클래스를 담을 수 있는 타입 
	 
	//** 다른점 객체가 담기는게 아님, 즉 붕어빵 틀~!이 담길 수 있다. 
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABullet> BulletFactory;
	//Abullet에는 엔진에서 만든 Bp bullet도 들어갈 수 있다. 

	UPROPERTY(EditAnywhere)
	class UInputMappingContext* IMC_PlayerInput;

	UPROPERTY(EditAnywhere)
	class UInputAction* IA_Horizontal;

	UPROPERTY(EditAnywhere)
	class UInputAction* IA_Vertical;

	UPROPERTY(EditAnywhere)
	class UInputAction* IA_Fire;


	UPROPERTY(EditAnywhere)
	float MoveSpeed = 500.0f;

private:
	float Horizontal;
	float Vertical;

private:
	//이벤트 발생시 실행 될 함수
	// FInputActionvalue 사용하려면 
	// #include "InputActionValue.h"추가 해야 함.
	// float 1인지 -1 인지 알아야된다. 
	void OnInputHorizontal(const struct FInputActionValue& value);
	void OnInputVertical(const struct FInputActionValue& value);

	//fire 매개변수 없는 이유 ,, IA Fire는 bool이기 때문에, 함수만 들어오면 그게 true인거다.
	void Fire();

};
