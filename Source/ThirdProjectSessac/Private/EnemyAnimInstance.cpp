// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"
#include "Enemy.h"

void UEnemyAnimInstance::AnimNotify_AttackStart()
{
	AEnemy* Enemy = Cast<AEnemy>(TryGetPawnOwner());
}

void UEnemyAnimInstance::AnimNotify_AttackEnd()
{

}
