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

protected:
	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(EditAnywhere, meta = (Bindwidget))
	class UButton* Button_Restart;

	UPROPERTY(EditAnywhere, meta = (Bindwidget))
	class UButton* Button_Quit;

public:
	UFUNCTION()
	void RestartLevel();

	UFUNCTION()
	void Quit();

};
