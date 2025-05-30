// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DodgeballProjectile.generated.h"

UCLASS()
class DODGEBALL2_API ADodgeballProjectile : public AActor{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADodgeballProjectile();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

	// 닷지볼이 표면에 튕길 때 재생할 사운드, BP_닷지볼프로젝타일에 추가함
	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundBase* BounceSound;

	// 이전 사운드의 사운드 감쇄 (sound attenuation)
	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundAttenuation* BounceSoundAttenuation;

	// 플레이어가 맞았을 때 닷지볼이 생성할 파티클 시스템
	UPROPERTY(EditAnywhere, Category = Particles)
	class UParticleSystem* HitParticles;

	// 플레이어가 맞았을 때의 사운드
	UPROPERTY(EditAnywhere, Category = Particles)
	class USoundBase* DamageSound;

	// 닷지볼이 플레이어 캐릭터에게 입힐 데미지
	UPROPERTY(EditAnywhere, Category = Damage)
	float Damage = 34.f;

	// OnHit 이벤트 발생하면 호출될 함수를 생성해야 하므로 UFUNCTION() 매크로를 가져야하고 public으로 선언해야함.
public:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// DodgeballProjectile 클래스의 ProjectileMovement 속성에 대한 접근 함수 추가
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovementComponent() const { return ProjectileMovement; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
