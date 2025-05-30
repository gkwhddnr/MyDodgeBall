// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "HealthInterface.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UHealthComponent::LoseHealth(float Amount) {
	Health -= Amount;

	if (GetOwner()->Implements<UHealthInterface>()) {
		IHealthInterface::Execute_OnTakeDamage(GetOwner());
	}
	if (Health <= 0.f) {
		Health = 0.f;
		// UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
		if (GetOwner()->Implements<UHealthInterface>()) {
			// 참이면 소유자가 HealthInterface를 구현했다는 것을 의미하므로 IHealthInterface를 사용
			// 인터페이스 호출함수는 항상 앞에 Execute_ 접두사가 붙은 이름을 가짐 (빨간줄로 오류나는데 무시한다.)
			IHealthInterface::Execute_OnDeath(GetOwner());
		}
	}
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

