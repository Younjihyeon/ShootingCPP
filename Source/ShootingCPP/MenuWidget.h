// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere, meta = (Bindwidget))
	class UButton* Button_Restart;

	UPROPERTY(EditAnywhere, meta = (Bindwidget))
	class UButton* Button_Quit;


};
