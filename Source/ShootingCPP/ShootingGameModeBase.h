// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootingGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_API AShootingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	int32 CurrentScore = 0;
	//찍어낸 붕어빵 UMainWidget이나 자식 객체 
	class UMainWidget* MainUI;


	class UMenuWidget* MenuUI;

	

	//붕어빵 틀 UMainWidget이나 자식 클래스 
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainWidget> MainWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMenuWidget> MenuWidgetClass;

public:
	void AddScore(int32 Point);

	void ShowMenu();

protected:
	virtual void BeginPlay() override;




};
