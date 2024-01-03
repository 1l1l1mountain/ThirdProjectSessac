// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyFunction.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPROJECTSESSAC_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EEnemyState State;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsFalled;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsFast;


	UFUNCTION()
	void AnimNotify_AttackStart();
	
	UFUNCTION()
	void AnimNotify_AttackEnd();
	UFUNCTION()
	void AnimNotify_JumpEnd();
	
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
}; 
