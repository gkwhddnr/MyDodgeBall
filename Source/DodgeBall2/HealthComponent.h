// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DODGEBALL2_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	// 소유자의 초기 및 현재 체력 점수의 양
	UPROPERTY(EditAnywhere, Category = Health)
	float Health = 100.f;

public:
	void LoseHealth(float Amount);

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 게임의 오브젝트가 갖는 최대 체력 수치를 100이라 가정하고 Health 속성을 100으로 나누어 값을 반환함.
	FORCEINLINE float GetHealthPercent() const { return Health / 100.f; }

		
};
