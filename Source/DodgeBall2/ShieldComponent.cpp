#include "ShieldComponent.h"

#include "GameFramework/Actor.h"
#include "TimerManager.h"

UShieldComponent::UShieldComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MaxShield = 100.0f;
	CurrentShield = MaxShield;
	RechargeRate = 10.0f;
	RechargeDelay = 2.0f;
	bIsDepleted = false;
	bCanRecharge = true;
}

void UShieldComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentShield = FMath::Clamp(CurrentShield, 0.0f, MaxShield);
	bIsDepleted = (CurrentShield <= 0.0f);
}

void UShieldComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bCanRecharge && !bIsDepleted && CurrentShield < MaxShield && RechargeRate > 0.0f)
	{
		CurrentShield += RechargeRate * DeltaTime;

		if (CurrentShield >= MaxShield)
		{
			CurrentShield = MaxShield;
		}
	}
}

float UShieldComponent::AbsorbDamage(float DamageAmount)
{
	if (DamageAmount <= 0.0f)
	{
		return 0.0f;
	}

	// 데미지 발생 시 회복 잠시 중단
	OnDamageTaken();

	if (bIsDepleted || CurrentShield <= 0.0f)
	{
		// 실드가 없으면 전부 Health로 넘어감
		bIsDepleted = true;
		return DamageAmount;
	}

	const float DamageApplied = FMath::Min(CurrentShield, DamageAmount);
	CurrentShield -= DamageApplied;

	if (CurrentShield <= 0.0f)
	{
		CurrentShield = 0.0f;
		bIsDepleted = true;
	}

	// 실드로 막지 못한 남은 데미지
	const float RemainingDamage = DamageAmount - DamageApplied;
	return RemainingDamage;
}

void UShieldComponent::ResetShield()
{
	CurrentShield = MaxShield;
	bIsDepleted = false;
	bCanRecharge = true;

	if (AActor* Owner = GetOwner())
	{
		Owner->GetWorldTimerManager().ClearTimer(RechargeDelayTimerHandle);
	}
}

bool UShieldComponent::IsShieldActive() const
{
	return (CurrentShield > 0.0f && !bIsDepleted);
}

void UShieldComponent::OnDamageTaken()
{
	bCanRecharge = false;

	if (AActor* Owner = GetOwner())
	{
		Owner->GetWorldTimerManager().ClearTimer(RechargeDelayTimerHandle);
		Owner->GetWorldTimerManager().SetTimer(
			RechargeDelayTimerHandle,
			this,
			&UShieldComponent::EnableRecharge,
			RechargeDelay,
			false);
	}
}

void UShieldComponent::EnableRecharge()
{
	if (!bIsDepleted)
	{
		bCanRecharge = true;
	}
}

