#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShieldComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DODGEBALL2_API UShieldComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UShieldComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** 최대 실드량 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield")
	float MaxShield;

	/** 현재 실드량 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shield")
	float CurrentShield;

	/** 초당 회복량 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield")
	float RechargeRate;

	/** 피격 후 회복이 시작되기까지의 지연 시간(초) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield")
	float RechargeDelay;

	/** 실드가 완전히 소모되었는지 여부 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shield")
	bool bIsDepleted;

	/** 실드가 현재 회복 가능한 상태인지 여부 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shield")
	bool bCanRecharge;

	/**
	 * 데미지를 실드로 먼저 흡수하고, 남은 데미지를 반환
	 * 반환값: 실드로 막지 못하고 건강(Health)으로 넘어가야 할 데미지
	 */
	UFUNCTION(BlueprintCallable, Category = "Shield")
	float AbsorbDamage(float DamageAmount);

	/** 실드를 최대치로 리셋 */
	UFUNCTION(BlueprintCallable, Category = "Shield")
	void ResetShield();

	/** 실드가 어느 정도라도 남아 있는지 여부 */
	UFUNCTION(BlueprintCallable, Category = "Shield")
	bool IsShieldActive() const;

protected:
	FTimerHandle RechargeDelayTimerHandle;

	/** 피격 직후 회복 잠시 중단 */
	void OnDamageTaken();

	/** RechargeDelay 후 호출되어 회복 재시작 */
	void EnableRecharge();
};

