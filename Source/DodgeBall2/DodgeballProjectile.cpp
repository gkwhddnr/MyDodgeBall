// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgeballProjectile.h"
#include "HealthComponent.h"
#include "DodgeBall2Character.h"
#include "Components/SphereComponent.h"
#include "Gameframework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ADodgeballProjectile::ADodgeballProjectile(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereComponent->SetSphereRadius(35.f);

	// 생성한 Dodgeball 프리셋으로 설정
	SphereComponent->SetCollisionProfileName(FName("Dodgeball"));
	SphereComponent->SetSimulatePhysics(true);		// 피직스 시뮬레이션

	// OnHit 이벤트 호출
	SphereComponent->SetNotifyRigidBodyCollision(true);

	// 추가한 함수와의 바인딩을 통해 OnComponentHit 이벤트를 받도록 설정
	SphereComponent->OnComponentHit.AddDynamic(this, &ADodgeballProjectile::OnHit);

	// 이 sphere 컴포넌트를 Root  컴포넌트로 설정
	// 이렇게 설정 안하면 충돌(콜리전)이 제대로 동작하지 않을 수 있음.
	RootComponent = SphereComponent;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = 1500.f;

}

void ADodgeballProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	// 형변환하기 이전에 설정, 닷지볼이 표면에 굴러갈 때 여러 번 튀는 소리 재생하지 않기 위해 설정
	if(BounceSound != nullptr && NormalImpulse.Size() > 600.f){
		UGameplayStatics::PlaySoundAtLocation(this, BounceSound, GetActorLocation(), 1.f, 1.f,0.f,BounceSoundAttenuation);
	}

	// OtherActor를 ADodgeball2Character 클래스로 형변환하고 형변환 후 값이 nullptr이 아닌지 확인
	ADodgeBall2Character* Player = Cast<ADodgeBall2Character>(OtherActor);
	if (Player != nullptr) {
		UHealthComponent* HealthComponent = Player->FindComponentByClass<UHealthComponent>();

		if (HealthComponent != nullptr) {
			HealthComponent->LoseHealth(Damage);
		}
		// 형변환하기 이전에 설정, HitParticles 속성이 유효한지 확인
		if (HitParticles != nullptr) UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, GetActorTransform());
		if (DamageSound != nullptr) UGameplayStatics::PlaySound2D(this, DamageSound);

		Destroy();
	}
}


// Called when the game starts or when spawned
void ADodgeballProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(5.f);
}

// Called every frame
void ADodgeballProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

