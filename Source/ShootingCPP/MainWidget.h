// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	
	//UTextBlock은 widget에서 Text 
	//Bindwidget 명령어는UMainWidget을 만들면 Bindwidget된 ScoreText는 반드시 만들도록 강제한다.
	//그리고 ScoreText와 이름이 같은 text를 만들면 자동으로 scoretext와 연동해준다.
	UPROPERTY(EditAnywhere, meta = (Bindwidget))
	class UTextBlock* ScoreText;

	//ScoreData와 이름이 같은 텍스트를 만들면 자동으로 ScoreData와 연동해준다. 
	UPROPERTY(EditAnywhere, meta = (Bindwidget))
	class UTextBlock* ScoreData;

public:
	void PrintScore(int32 CurrentScore);
};
