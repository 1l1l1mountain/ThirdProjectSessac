// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFunction.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle UMETA(DisplayName = "IDLE"),
	Move UMETA(DisplayName = "MOVE"),
	Attack UMETA(DisplayName = "ATTACK"),
	Damage UMETA(DisplayName = "DAMAGE"),
	Die UMETA(DisplayName = "DIE"),


};
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPROJECTSESSAC_API UEnemyFunction : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyFunction();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	class AEnemy* Enemy;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	EEnemyState State;

	UPROPERTY()
	class AMyPlayer* Player;

	void TickIdle();
	void TickMove();
	void TickAttack();
	void TickDamage();
	void TickDie();
	void SetState(EEnemyState next); // Ŭ���� �ȿ��� �Լ��� �Ű�������, ��������̸��� ������ �ȵǳ� ��.
	
	
	
	//�÷��̾�� ������ �ִ� �Լ� �߰��ϱ�

};
