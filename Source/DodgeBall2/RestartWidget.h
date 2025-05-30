// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RestartWidget.generated.h"

/**
 * 
 */
UCLASS()
class DODGEBALL2_API URestartWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(/*1*/meta = (BindWidget, /*2*/OptionWidget = true))	// 1. 클래스 상속하는 블루프린트 클래스 버튼에 이 속성을 연결해야 함.
	// 2. 이 C++클래스를 상속하는 위젯 블루프린트에 동일한 타입과 이름의 요소가 없는 경우 컴파일 오류 발생을 방지
	class UButton* RestartButton;

	UPROPERTY(/*1*/meta = (BindWidget, /*2*/OptionWidget = true))
	class UButton* ExitButton;

public:
	virtual void NativeOnInitialized() override;


protected:
	UFUNCTION()
	void OnRestartClicked();

	UFUNCTION()
	void OnExitClicked();
};
