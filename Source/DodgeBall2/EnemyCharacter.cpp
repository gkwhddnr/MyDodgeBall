// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "DodgeballProjectile.h"
#include "Engine/World.h"
#include "LookAtActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Gameframework/ProjectileMovementComponent.h"
#include "GameFramework/Actor.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter(){
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LookAtActorComponent = CreateDefaultSubobject<ULookAtActorComponent>(TEXT("Look At Actor Component"));
	LookAtActorComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// 현재 플레이어가 제어하는 캐릭터 구하기
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

	// 매 프레임 플레이어 캐릭터를 바라본다.
	LookAtActorComponent->SetTarget(PlayerCharacter);
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	
	bCanSeePlayer = LookAtActorComponent->CanSeeTarget();

	if (bCanSeePlayer != bPreviousCanSeePlayer) {
		if (bCanSeePlayer) { // 닷지볼 던지기 시작
			GetWorldTimerManager().SetTimer(ThrowTimerHandle, this, &AEnemyCharacter::ThrowDodgeball, ThrowingInterval, true, ThrowingDelay);
		}
		else {	// 닷지볼 던지기 멈춤
			GetWorldTimerManager().ClearTimer(ThrowTimerHandle);
		}
	}

	bPreviousCanSeePlayer = bCanSeePlayer;

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// 전달된 액터를 바라보도록 캐릭터 회전 변경
/*
bool AEnemyCharacter::LookAtActor(AActor* TargetActor) {
	if (!TargetActor) {
		return false;
	}

	const TArray<const AActor*> IgnoreActors = { this, TargetActor };
	
	if(UDodgeballFunctionLibrary::CanSeeActor(GetWorld(),SightSource->GetComponentLocation(),TargetActor,IgnoreActors)){
		FVector Start = GetActorLocation();
		FVector End = TargetActor->GetActorLocation();

		// 시작 지점에서 끝 지점을 바라보는 데 필요한 회전 계산
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

		// 적의 회전을 앞서 구한 회전 값으로 설정
		SetActorRotation(LookAtRotation);
		return true;
		
	}

	return false;
}
*/


// 전달된 액터를 볼 수 있는지 확인
/*
bool AEnemyCharacter::CanSeeActor(const AActor* TargetActor) const {
	if (!TargetActor) {
		return false;
	}
	// 라인 트레이스 결과 저장, 스윕 트레이스도 필요
	FHitResult Hit;

	// 라인 트레이스의 시작과 끝, 스윕 트레이스도 필요
	FVector Start = SightSource->GetComponentLocation();
	FVector End = TargetActor->GetActorLocation();

	// 스윕 트레이스에서 사용되는 모형의 회전
	FQuat Rotation = FQuat::Identity;

	// 시야 판단을 위해 비교할 트레이스 채널, 스윕 트레이스도 필요
	ECollisionChannel Channel = ECollisionChannel::ECC_GameTraceChannel1;

	// 스윕 트레이스에서 사용하는 객체 모형
	FCollisionShape Shape = FCollisionShape::MakeBox(FVector(20.f, 20.f, 20.f));

	// 라인 트레이스가 적 캐릭터는 무시하도록 설정
	FCollisionQueryParams QueryParams;

	// 이 라인 트레이스를 실행하는 액터 무시
	QueryParams.AddIgnoredActor(this);

	// 확인할 대상 액터를 무시할 액터 목록 추가
	QueryParams.AddIgnoredActor(TargetActor);

	// 라인 트레이스 실행
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, Channel, QueryParams);

	// 스윕 트레이스 실행
	// GetWorld()->SweepSingleByChannel(Hit, Start, End, Rotation, Channel, Shape);

	// 게임에서 라인 트레이스 보여주기 (시각화)
	DrawDebugLine(GetWorld(), Start, End, FColor::Red);


	// 충돌한 대상이 있는지 확인
	return !Hit.bBlockingHit;
}
*/

void AEnemyCharacter::ThrowDodgeball() {
	if (!DodgeballClass) {
		return;
	}
	FVector ForwardVector = GetActorForwardVector();
	float SpawnDistance = 40.f;
	FVector SpawnLocation = GetActorLocation() + (ForwardVector * SpawnDistance);
	FTransform SpawnTransform(GetActorRotation(),SpawnLocation);

	// 새 닷지볼 스폰하기
	ADodgeballProjectile* Projectile = GetWorld()->SpawnActorDeferred<ADodgeballProjectile>(DodgeballClass, SpawnTransform);
	Projectile->GetProjectileMovementComponent()->InitialSpeed = 2200.f;
	Projectile->FinishSpawning(SpawnTransform);
}