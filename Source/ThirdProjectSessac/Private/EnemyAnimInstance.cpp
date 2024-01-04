// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"
#include "Enemy.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UEnemyAnimInstance::AnimNotify_AttackStart()
{
	AEnemy* Enemy = Cast<AEnemy>(TryGetPawnOwner());
	Enemy->RightHandCollision->SetCollisionProfileName("EnemyWeapon");
	Enemy->LeftHandCollision->SetCollisionProfileName("EnemyWeapon");
}

void UEnemyAnimInstance::AnimNotify_AttackEnd()
{
	AEnemy* Enemy = Cast<AEnemy>(TryGetPawnOwner());
	Enemy->RightHandCollision->SetCollisionProfileName("NoCollision");
	Enemy->LeftHandCollision->SetCollisionProfileName("NoCollision");

}
//점프가 끝나면 이동 상태로 변환
void UEnemyAnimInstance::AnimNotify_JumpEnd()
{
	AEnemy* Enemy = Cast<AEnemy>(TryGetPawnOwner());
	if (Enemy->FunctionComp != nullptr)
	{

		Enemy->FunctionComp->SetState(EEnemyState::Move);
	}
}
//틱 불러오기
void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	AEnemy* Enemy = Cast<AEnemy>(TryGetPawnOwner());
	if (Enemy != nullptr)
	{

		bIsFalled = (!Enemy->GetCharacterMovement()->IsFalling());

	}


}
