// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgeballPlayerController.h"
#include "HUDWidget.h"
#include "RestartWidget.h"

// 플레이어가 죽으면 RestartWidget 생성
void ADodgeballPlayerController::ShowRestartWidget() {
	if (BP_RestartWidget != nullptr) { // BP_RestartWidget = true
		// 게임실행을 멈추고 UI가 나타남.
		SetPause(true);
		// UI Only 입력모드로 업데이트
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;

		// 위젯 생성
		RestartWidget = CreateWidget<URestartWidget>(this, BP_RestartWidget);
		RestartWidget->AddToViewport();
	}
}

// 메뉴 옵션을 선택하면 없앰.
void ADodgeballPlayerController::HideRestartWidget() {
	RestartWidget->RemoveFromParent();
	RestartWidget->Destruct();

	// 게임실행되고 마우스커서를 숨김.
	SetPause(false);
	// GameOnly 모드로 업데이트
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

void ADodgeballPlayerController::BeginPlay() {
	Super::BeginPlay();

	if (BP_HUDWidget != nullptr) {
		HUDWidget = CreateWidget<UHUDWidget>(this, BP_HUDWidget);
		HUDWidget->AddToViewport();
	}
}

void ADodgeballPlayerController::UpdateHealthPercent(float HealthPercent) {
	if (HUDWidget != nullptr) {
		HUDWidget->UpdateHealthPercent(HealthPercent);
	}
}