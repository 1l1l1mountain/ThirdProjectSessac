// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"
#include "Enemy.h"
#include "Components/SphereComponent.h"

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
