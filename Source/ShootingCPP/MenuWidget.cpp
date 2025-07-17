// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMenuWidget::NativeConstruct()
{
	//잊지말기!
	Super::NativeConstruct();
	Button_Restart->OnClicked.AddDynamic(this, &UMenuWidget::RestartLevel);
	Button_Quit->OnClicked.AddDynamic(this, &UMenuWidget::Quit);
}

void UMenuWidget::RestartLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), "ShootingMap");
}

void  UMenuWidget::Quit()
{

	UWorld* Currentworld = GetWorld();
	//네번째 매개변수 bool BignorePlatformRestrictions의 의미는
	//플랫폼에서 직접 종료하는 로직을 제한할때 그 정책을 따르지에 대한 의미이다.
	//false를 하면 플랫폼의 정책을 따른다는 의미이고 true 를 한다면 정책에 따르지 않고 종료하겠다는 의미이다. 
	UKismetSystemLibrary::QuitGame(Currentworld, Currentworld->GetFirstPlayerController(),
		EQuitPreference::Quit, false);

}
