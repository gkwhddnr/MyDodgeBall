// Fill out your copyright notice in the Description page of Project Settings.


#include "RestartWidget.h"
#include "DodgeballPlayerController.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void URestartWidget::OnRestartClicked() {
	// PlayerController 타입의 이 위젯을 소유하는 플레이어를 구하고 클래스 형변환
	ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr) {
		PlayerController->HideRestartWidget();
	}
	UGameplayStatics::OpenLevel(this, FName(*UGameplayStatics::GetCurrentLevelName(this)));
}

void URestartWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();
	if (RestartButton != nullptr) {	// RestartButton = true
		RestartButton->OnClicked.AddDynamic(this, &URestartWidget::OnRestartClicked);
	}

	if (ExitButton != nullptr) {
		ExitButton->OnClicked.AddDynamic(this, &URestartWidget::OnExitClicked);
	}
}

void URestartWidget::OnExitClicked() {
	UKismetSystemLibrary::QuitGame(this,nullptr,EQuitPreference::Quit,true);
}