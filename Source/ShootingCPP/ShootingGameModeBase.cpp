// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.h"
#include "MenuWidget.h"


void AShootingGameModeBase::AddScore(int32 Point)
{
	CurrentScore += Point;

	//델리게이트로 onaddscoredelegate; 
	

	if (MainUI !=nullptr)
	{
		MainUI->PrintScore(CurrentScore);
	}
	

}

void AShootingGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//매개변수가 유효하지 않다면 에러로그를 1번 출력한다. 
	ensure(MainWidgetClass);

	//위젯은 CreateWidget 함수로 생성한다. 
	//위젯을 생성했다고 뷰포트에 출력되는것은아니다. 
	MainUI = CreateWidget<UMainWidget>(GetWorld(), MainWidgetClass);
	ensure(MainUI);
	//위젯을 뷰포트에 출력
	MainUI->AddToViewport();

}
void AShootingGameModeBase::ShowMenu()
{
	//매개변수가 유효하지 않다면 에러로그를 1번 출력한다. 
	ensure(MenuWidgetClass);

	//위젯은 CreateWidget 함수로 생성한다. 
	//위젯을 생성했다고 뷰포트에 출력되는것은아니다. 
	MenuUI = CreateWidget<UMenuWidget>(GetWorld(), MenuWidgetClass);
	ensure(MenuUI);
	//위젯을 뷰포트에 출력
	MenuUI->AddToViewport();

}

