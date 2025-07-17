// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "Components/TextBlock.h"

void UMainWidget::PrintScore(int32 CurrentScore)
{


	{
		FText CurrentScoreText = FText::AsNumber(CurrentScore);
		//텍스트 블록에는 덱스트형식만 들어갈수 있다.
		//즉 currentsocre는 int32타입이라 그냥은 못들어간다.
		//그래서 FText::AsNumber를 사용해서 FText형변환을 해서 넣어주는 것 .
		ScoreData->SetText(CurrentScoreText);
	}
}