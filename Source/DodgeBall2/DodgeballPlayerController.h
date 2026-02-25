// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DodgeballPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DODGEBALL2_API ADodgeballPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class URestartWidget> BP_RestartWidget;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UHUDWidget> BP_HUDWidget;

private:
	UPROPERTY()	// 블루프린트에서 편집할 수 없지만 UPROPERTY() 매크로로 지정하지 않으면 가비지 컬렉터가 삭제함.
	class URestartWidget* RestartWidget;

	UPROPERTY()
	class UHUDWidget* HUDWidget;

protected:
	virtual void BeginPlay() override;

public:
	void ShowRestartWidget();
	void HideRestartWidget();
	void UpdateHealthPercent(float HealthPercent);
};
